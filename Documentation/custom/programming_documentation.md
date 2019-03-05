# Programming Documentation {#programming}

# Introduction

This document is intended for programmers who already understand the functions of ourplugin, know the basics of programming in Unreal Engine 4 and who wish to understand the inner workings of our plugin and who might even want to extend it. In the first chapter, which you are reading right now, we will explain the structure of the document. We will also mention things you should have done and should know before reading the rest of the document. In the next chapter we will introduce the basic structure of the plugin, as well as some principles that apply throughout the plugin. The chapter after that will give you a high level overview of the functionality of this plugin. After that we will explain some basic ways how you can extend the plugin functionality. And in the last chapter we will share some tips and tricks we think might be useful. We will also explain some problems we found during the development, so you can avoid repeating our mistakes.

## Requirements

We expect that the reader has already installed the plugin according to the Adventure Plugin Installation Guide. The reader should have set up Visual Studio as explained in the guide and should be able to launch the development project from source.

The reader should have also already read the Adventure Plugin Designer Guide and should be familiar with terms like Quest Editor, Dialog Editor, Inventory Item Blueprint etc. She should be at least familiar with everything our plugin can and cannot do.

The reader must know the basics of C++ development, programming in Unreal Engine 4 and specifically she should know how to create plugins. If you are not familiar with programming in Unreal Engine, you should find some information here:

* Here you can find general information about programming in Unreal Engine

    * [https://docs.unrealengine.com/en-us/Programming](https://docs.unrealengine.com/en-us/Programming)

* Here in particular is a great video for getting started with plugin development:

    * C++ Extending the Editor | Live Training | Unreal Engine:

[https://www.youtube.com/watch?v=zg_VstBxDi8](https://www.youtube.com/watch?v=zg_VstBxDi8)

You should also be aware of the Unreal Engine coding standard. We tried to follow it as much as we could, although we did mostly ignore the rules about passing arguments by reference and using const often. That is because it caused problems with some blueprint nodes and we wanted to be consistent throughout the project. The style guide is available here:

* [https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard](https://docs.unrealengine.com/en-us/Programming/Development/CodingStandard)

When designing the Dialog Graph and Quest Graph classes, we based our code on an already existing plugin called Generic Graph. If you ever have trouble understanding our modified version of the code, it might be helpful to check out the original version we started with, which might be easier to understand.

* [https://github.com/jinyuliao/GenericGraph](https://github.com/jinyuliao/GenericGraph)

# Basics

In this chapter we will introduce information that will be useful to you, no matter what you plan to do. We will also explain some Unreal Engine 4 concepts that are might not be known to beginners.

First of all, note that the code is documented and that there is a generated reference documentation included in the plugin package. This means that we will not be describing individual classes in this document. This document is meant to give you a high level overview of the plugin functionality so it is easier to understand.

All public methods assume that they might be given invalid parameters, even if they are not directly callable from blueprints. So all of our public methods check the input parameters before doing anything. If they are invalid, the method is expected to do nothing, return a value least likely to cause any problems and log an error. Sometime we also use assertions instead of logging errors - that is when we are absolutely certain that this problem is a developer oversight, like not overriding a method and calling a pure virtual function. But even in those cases the plugin will not crash when in release mode.

Speaking of pure virtual functions - Unreal Engine 4 does not support them, at least not directly. The problem is with Class Default Objects. For each object, even an abstract one, Unreal Engine 4 generates an instance of that object called Class Default Object. And you cannot instantiate a class with pure virtual functions. Unreal Engine does provide a macro PURE_VIRTUAL the programmers can use to identify them, but we do not use it because for two main reasons:

* PURE_VIRTUAL macro is not recognized by doxygen, so the information would not be visible in documentation.

* PURE_VIRTUAL macro expands to code which causes fatal errors, which in turn deliberately crash the application. We do not want that. Even though calling a pure virtual function is definitely an error, we want to avoid crashing the application if possible.

* PURE_VIRTUAL macro is undocumented and we want to avoid using undocumented features if possible.

We already mentioned what Class Default Objects, or CDO for short, are. As we use them frequently throughout the plugin, we should probably introduce the object more. There are few basic ways of working with the CDOs:

* Unreal Engine 4 uses them to create instances of that specific class. So when you want to create a new instance of a class, constructor is not called. Instead the CDO is just copied to another place in memory, creating a new instance of this class. While this might sound like an internal Unreal Engine 4 thing, it is important to be aware of this, as this is the main reason why you should not modify the CDO of a class unless you really know what you are doing.

* We use them frequently to access the default values. For example, when creating a thumbnail for an Adventure Character blueprint, we do not have an instance of the Adventure Character class, just the UClass specifying which UAdventureCharacter subclass the asset represents. However, we can get a CDO of that UClass, cast it to UAdventureCharacter and get the icon of that character from there. And we could not do that using static methods, as we can only cast the CDO to UAdventureCharacter class, as we have no idea which specific class the blueprint represents.

* Class defaults are visible in the blueprint editor, so we can use the CDO of a class to display something to the designer. We use Class Default Objects to display registered combinations. However, be careful about modifying CDOs. All new instances of that class will also have those variables you modified on the CDO. We can use it in this case only because the variables modified are used only in editor. So they cannot affect the game itself.

Game context is often passes as a parameters and checking if it is valid is a very common procedure. Because of that, UAdventurePluginGameContext class has a static method IsGameContextValid, which you can use to verify if the game context and all of its subclasses are valid.

Speaking of validating, if you want your methods to check whether some variables are valid, we recommend you to not just check whether the variable is null, but to call the IsValid global method from Unreal Engine 4. This method does return false if the passed object is nullptr, but it also returns false if the object is about to be destroyed. That should not normally happen, but when it does those bugs are difficult to find and debug.

## Plugin Structure

When you open the solution file for our plugin, you will see that the plugin is divided into 4 modules:

* AdventurePluginRuntime: This module contains all classes that are necessary when running a game based on our adventure plugin.

* AdventurePluginEditor: In this module you will find most of the classes used for extending the editor.

* AdventurePluginDialogEditor: This module is responsible for creating the dialog graph editor, as well as registering the customizations that create combobox pickers for dialog related properties and structures.

* AdventurePluginQuestEditor: This module is responsible for creating the quest editor, as well as registering the customizations that create combobox pickers for quest related properties and structures.

You might notice that all of our headers are in the Public folder. That is intentional. Our plugin is meant to be extended, so you should be able to inherit from all classes we created and use them for your own purposes.

# High Level Overview

This chapter should help you understand the plugin. However, we will not go into details that you can easily learn by reading the generated documentation and going through the code. We will first talk about the assets - Adventure Character, Inventory Item, Dialog Graph and Quest Graph. After that we will explain the functionality of the classes accessible through the Game Context. Last we will briefly mentioned additional classes that did not fit to any of these categories. 

## Assets

There are a number of classes that need to be set up for the assets to work correctly:

* Every asset has a class that actually represents the asset - UDialogGraph, UQuestGraph, UInventoryItem, UAdventureCharacter. These are the classes the designer is editing in graph editors and blueprint editors and which are accessible during runtime.

* We divide assets into two types: Blueprint Assets (UAdventureCharacter and UInventoryItem) and Data Assets (UQuestGraph and UDialogGraph).

    * When you create a new data asset, you do not create a new class, the asset is an instance of the corresponding class. This means that you can only modify properties of the graph, not its behavior. However, Unreal Engine handles access to data assets and has pickers with thumbnails for them by default.

    * When you create a blueprint asset, every asset you create is a subclass of the asset class. This means that you can modify methods of the class in blueprints, but Unreal Engine does not support pickers with thumbnails. When you need to select the asset in editor, you need to set it in a variable of type Class Reference, so you also need to convert the class reference from your variable to an instance of the class.

* For every asset we also have a factory class - UDialogGraphFactory, UQuestGraphFactory, UAdventureCharacterFactory, UInventoryItemFactory. These are required by Unreal Engine. They do not have to be registered anywhere, they are automatically detected by the engine. For Data Assets the factory only specifies that it can create an asset of the corresponding type. For Blueprint Assets the factory also defines which UBlueprint class should hold the newly created asset. The UBlueprint class can define thumbanils and are responsible for editing and compiling the class the blueprint represents.

* For data assets we have also created editors that can edit the asset - FAssetEditor_DialogGraph, FAssetEditor_QuestGraph. They will be described in more detail later in this chapter.

* We also had to create the FAssetTypeActions class for every asset - FAssetTypeActions_QuestGraph, FAssetTypeActions_DialogGraph, FAssetTypeActions_InventoryItem, FAssetTypeActions_AdventureCharacter. These are used to add the asset to the content browser’s menu. For data assets they also define which editor should be opened when editing that asset by overriding the OpenAssetEditor method. Without this a generic Data Asset editor would open. These must be explicitly registered in some module in the StartupModule method and unregistered in the ShutdownModule method.

The rest of the the functionality regarding assets, mainly about editing them, is specific to data assets and blueprint assets. Data assets share common functionality, as they are both graphs and use very similar graph editors. Blueprint assets both represent combinable objects and also share most of the functionality.

### Graph Editors

Both Dialog Graph Editor and the Quest Graph Editor extend a Generic Graph Editor, a third party class mentioned in the beginning of the document. 

The nodes in the graph represent runtime objects, as they are referenced when running the game, i.e. when executing dialogs and changing quest properties. The UQuestGraph and UDialogGraph classes have a NodeType property, which define which runtime nodes can actually appear in the graph. For UQuestGraph it is the UQuestGraphNode class and for UDialogGraph it is the UDialogGraphNode class. The graph editor automatically gathers all non-abstract classes which inherit from NodeType and allows them to be inserted into the graph.

However, the runtime nodes only define how the nodes behave during runtime. They have a few editor only properties that can change minor things like a node’s color, whether it can be deleted etc., but if you want to do major changes, you need to create your own class to do that. Normally quest nodes are displayed using the UEdQuestNode class and dialog nodes are displayed using the UEdDialogNode class. When creating custom editor nodes it might be enough to just create a subclass of the appropriate editor node class and modify it. However, if you want to do larger UI changes you might need to create your own Slate objects, like SEdDialogNode and SEdQuestNode. These are Slate objects that define the node’s UI representation.

The editor nodes have to be explicitly registered to be useful. The Adventure Plugin Module has the RegisterEditorNodeForRuntimeNode method. This registers the editor node as a representation of the runtime node. The registered nodes also support inheritance, i.e. if a runtime node does not have an editor node registered, it checks whether the parent class has a registered node, or parent of the parent etc.

Now that you know what the node runtime nodes and editor classes are, we can explain how they are actually displayed. First you have the main Asset Editor classes, FAssetEditor_QuestGraph and FAssetEditor_DialogGraph. These define how will the editing window look. They contain a lot of functionality, but most of it is Unreal Engine boilerplate code that needs to be there for the windows to work correctly. It should be enough to just inherit from the FAssetEditor_GenericGraph class when creating your own graph. The important methods you might need to override are:

* GetViewPortWidgetAppearanceInfo: In this method you can set the name of the graph that appears in the bottom right corner of the editor.

* GetGraphSchemaClass: The Graph Schema mainly defines the editor behavior, i.e. which editor nodes correspond to which runtime nodes, which nodes can actually appear in the graph, what actions appear in context menus etc.

* RebuildGenericGraph: This method is called whenever the graph object should be rebuilt, i.e. when what is visualized in the graph editor should be saved to the asset object (the UDialogGraph and UQuestGraph object). That happens whenever when the graph is saved. You should override it if you want to save some additional data in the graph object. For example, for UDialogGraph we use this method to fill the map between node IDs and nodes, so the Goto node can just find the target node in the map instead of having to traverse the entire graph to find it.

Next there are the Schema classes, FAssetGraphSchema_QuestGraph and FAssetGraphSchema_DialogGraph. Again, the Generic Graph implementation does most of the heavy lifting, it finds all non-abstract subclasses of the runtime nodes that can be added, registers actions when you right click in the graph etc. The concrete implementations mainly specify the nodes that should be automatically added to new graphs.

Next we have customization classes, all classes ending in Customization. These are not strictly necessary for the editors to work, but they make the editor a lot more user friendly. There are two kinds of customizations:

* Detail customization: These customize some property editors in the property pane of a specific object. For example, Goto node has a detail customization, as it needs to know into which graph the node belongs, so it can find all the IDs in the graph and present them to the designer. These customizations must be explicitly registered and unregistered using the PropertyModule.(Un)RegisterCustomClassLayout method on plugin startup and shutdown.

* Property type customization: These customization specify that everywhere a specific struct appears, it should should use this customization to change its look in the property pane. For example, FQuestGraphBool structs has a property customization, as the struct defines both the quest and variable name, so wherever FQuestGraphBool appears as a property or variable, the editing field for that property can be replaced by the one specified in the customization. These customizations must be explicitly registered and unregistered using the PropertyModule.(Un)RegisterCustomPropertyTypeLayout method on plugin startup and shutdown.

These classes together create the graph and dialog editors with all of their features. We will not be discussing the actual asset classes, UQuestGraph and UDialogGraph, in detail here. And we will not describe the runtime nodes either. Quests should be easily understood from code and the only complex thing regarding dialogs is the actual dialog execution, which will be described in the section about the Dialog Controller class.

### Combinable blueprints

Both Adventure Character and Inventory Item classes inherit from the same class, UCombinableObject. And their respective blueprint classes inherit from the UCombinableObjectBlueprint class. These base classes give their children support for combinations.

The behavior specific to the child classes is quite simple, they just specify several simple methods, event dispatchers and properties that are exposed to blueprints, nothing else. So the UAdventureCharacter and UInventoryItem classes will not be described here.

As for the UCombinableObjectBlueprint subclasses, apart from the combination system, the only interesting fact is that the UAdventureCharacterBlueprint and UInventoryItemBlueprint classes implement the IIconThumbnailInterface, which we use to create thumbnails for our custom assets.

The combination system itself is also simple, the only part of the system worth describing is how do the combinations know about each other, how do the External Blueprint Combinations properties get filled on the UCombinableObject classes.

That is the responsibility of the UCombinableObjectBlueprint class. The Compiled method on this object is called every time this object is compiled. After compilation, the object will at first initialize to combination on the represented object’s CDO. After that, it will search for all assets inheriting from UCombinableObjectBlueprint, get the CDO of the classes they represent and update the combinations between these objects. Both the External Blueprint Combinations on this and on the target object.

## Game Context Objects

The UAdventurePluginGameContext methods provide most of the functionality to our objects. We will not describe the presenter classes here, as they are described sufficiently in the Designer Documentation. The rest of the classes will be described in individual sections.

### UDialogController

This class is responsible for playing dialogs. It can play only one dialog at a time. When you call the ShowDialog method, it set its property CurrentNode property to the node where the execution should start, either the main entry point or the node passed as an argument. After that it will follow this algorithm:

1. Call ShowDialog on the presenter

2. Call the Execute method on the current node. It can return either true or false.

    1. If It returns true, go to step 3 directly

    2. If it returns false, it means that a long running action was started. The execution should be temporarily halted and the method executing the graph will return, as some other object is now responsible for the flow of the dialog, usually the dialog presenter.

        1. Once the presenter finishes the execution, it will call the appropriate callback on the UDialogController, which will in turn call a similar callback on the current node. If the callback on the current node returns true, we continue from step 3, otherwise the callback was meant for something different and the execution should still be halted. There is no way of determining that a presenter forgot to call the callback. If that happens, the dialog will be stuck forever.

3. Call the GetNextNode method on the current node and set the current node to the value returned from that method.

4. If the current node is not null, go to 2.

5. Otherwise the dialog is over. Call Hide dialog.

The node also counts how many nodes were executed since the dialog execution started. If it reaches a large number, right now set to 100 000, the dialog will end. Otherwise the dialog could be stuck in a loop and run forever, freezing both the game and the editor.

### UInventoryController

UInventoryController does little by itself. It can return the current inventory and it can hide or show the inventory via the IInventoryPresenterInterface from game context.

The UInventory class was sufficiently described in the Designer Documentation. The only interesting thing is that it stores the list of items in inventory in the UAdventurePluginSaveGame object in the Game Context. And it saves that list in a constant location in the save game, so if you needed to support multiple inventories, you would need to override the UInventory class and override the SetItems and GetItems methods, so they load the items from a place dependent on the UInventory used.

The UInventoryItem class is sufficiently described in code and in the Designer Documentation.

### UAdventureCharacterManager/UInventoryItemManager

These classes are similar to each other, as they both inherit from the UCombinableObjectManager base class. They provide access to instances of the UAdventureCharacter and UInventoryItem classes and they call Init methods on newly created items and characters.

### UAdventurePluginSaveGame

This class in itself has little functionality, it just a place for other classes to store their data. But since all game data is in one object, saving a game is as easy as serializing this object, which can be done by calling the Save method on this object.

Adventure Plugin classes store and load persistent data directly on this object. So e.g. UInventory does not have the list of items stored in the class. Instead, when you call the GetItems method, it retrieves the current list of items from the UAdventurePluginSaveGame.

This approach makes saving very easy, but it might make the code less efficient and debugging slightly more difficult, as finding the correct variable in the save game might be difficult if you set hundreds of variables in your game. It might also be hard to maintain, as you must avoid duplicate data yourself. The quest variables solve this problem by including the path of the quest asset in the name of the variable when saving the game. However, that might make it even harder to find the correct variable value in the save game.

## Miscellaneous

Classes derived from UBlueprintLibrary are only wrappers that expose plugin functionality in a more blueprint friendly manner.

The UAdventurePluginConfig class contains the configuration the user can edit via Project Settings. It must be explicitly registered and unregistered in the UAdventurePluginEditor StartupModule and ShutdownModule methods.

The UAdventurePluginGameInstance class contains just the default game context and fills its values with instances found in the UAdventurePluginConfig defaults, which are loaded from the project configuration.

The UIconThumbnailRenderer can render thumbnails for classes implementing the IconThumbnailInterface. However, the thumbnails till have to be explicitly registered and deregistered in the UAdventurePluginEditor StartupModule and ShutdownModule for each class that uses it.

# Modifying the plugin

Here we will introduce some ways to modify the plugin to your own needs. This chapter is by no means exhaustive, you can modify the plugin as you see fit.

In general, there are two ways you can modify the plugin:

* Modify the plugin source directly. This is great for playing with the plugin and rapid prototyping. However, when we release a new version of the plugin, you will have a harder time merging our changes with your own.

* Create your own plugin that uses our plugin modules. You would also want to split your plugin into at least two modules, editor module and a runtime module. This way you could create custom implementations of our classes for the purposes of your game. And you would instruct your designers to use your classes instead of the ones provided by us.

You can combine these approaches. There are some modifications that are easy to do when modifying our plugin directly, yet almost impossible to do by inheriting our classes without massive rewrites. You can do these changes in your own fork of the plugin and do the simpler changes in your own plugin. If you limit the changes in your fork, pulling the changes from our updated version should be easier.

If your project is not blueprint only, you might not even need to create a plugin, as your project can extend our editors and classes just as well using C++ classes.

Before proceeding, most extensions are about adding more classes to the plugin - new nodes, new controllers, new managers. You should be thoroughly familiar with our implementations before creating your own.

In the first section of this chapter we will describe the ways to extend graphs. After that we will discuss potential ways to extend the other classes.

## Extending assets

The easiest way to extend the plugin is to create your own nodes. Creating a node is simple, just create a runtime class inheriting from either UDialogGraphNode or UQuestGraphNode. For the dialog node you need to correctly implement the Execute and GetNextNode method, for QuestGraphNode you need you need to implement the IsTrue method. There are a number of other things you can customize, see the UGenericGraphNode class to see all methods that you can override to alter the node’s looks and behavior. The easiest way to create a new node is to find a node most similar to what you are trying to do, copy paste it and modify it to suit your needs. Or to inherit from the similar node.

If your nodes require more drastic UI changes, like for example the DialogGraphNode_Options, you might need to register a custom UEdNode. You can register it by calling the RegisterEditorNodeForRuntimeNode method on the AdventurePluginEditor module.

Creating dialog graph nodes that do long running actions, like displaying dialog lines, is a bit more complicated. See the UDialogGraphNode_DialogLineBase class for inspiration. You need to create an interface for your node to handle the callback. You will also need to modify the UDialogController, to accept the callback, as blueprints cannot access the graph nodes directly. Or you can of course create a UDialogController subclass and use that instead.

UDialogGraphNode_DialogLineBase is also has a picker that allows the designer to select the talking animation from a list of talking animations defined on the animated character. So if you are creating custom dialog line nodes, they should still inherit from this base class, as they will handle both the talking animation and the show dialog line callbacks.

When creating a new dialog branching node that can continue from either a True or False pin, we recommend you to subclass that node from the UDialogGraphNode_TrueFalse class. You will only need to override the IsTrue method, as the GetNextNode and Execute methods are already handled in the base class and the appropriate editor node is already registered.

If you want to create a dialog node that can play an animation, it should inherit from the UDialogGraphNode_PlayAnimationBase class. If you implement the virtual methods correctly, the plugin will automatically create a picker that will let the designer select from the list of animations defined on the animated object.

Item related dialog nodes should inherit from the UDialogGraphNode_ItemBase class, for which a customization is registered that allows the designer to select the item from a picker with item thumbnails, instead of the default TSubclassOf<UInventoryItem> picker without images.

If you want to hide a node, maybe because you created your own subclass of that node and you do not want the designer to use the old ones by mistake, a quick and dirty way to do this is to make the old classes Abstract, as abstract nodes are skipped when finding a list of nodes the designer can create. This modification is also easy to handle during a merge with a newer plugin version.

Extending UDialogGraph or UQuestGraph classes is not easy, as Data Assets do not handle inheritance correctly. We recommend you to extend these classes directly without subclassing. The other option is to create completely new graphs yourself, which would probably require significant rewrites.

## Extending Game Context Classes

Extending these classes is easy, just create your own subclasses of those classes and make sure that the game context used by the designers uses your subclasses. Just make sure that the classes have still the same behavior as the old one. Also, make sure that the blueprint library methods still work or delete them if they are obsolete for your plugin.

For UAdventureCharacter and UItemManager subclasses, make up to instance of any UAdventureCharacter and UInventoryItem exists at any given time and that you call the Init method on them before the are used.

When subclassing UDialogController, make sure that either:

* The regular Execute/GetNextNode algorithm is still the same.

* Or hide the old nodes and create your own nodes.

* Or modify the old nodes to handle the new way of handling dialogs. 

You will also quite likely have to subclass the controller to create handlers for long running dialog operations if you create your own special nodes that require that.

The most likely reason to subclass the UInventoryController would be to add support for multiple inventories. In that case, make sure that your UInventory classes persist their inventories in different location, because right now the UInventory class persists its list of items in a specific place in the save game that is the same for all UInventory instances.

If you modify the UInventoryController or the UDialogController, make sure to also modify the presenters to work correctly with your modified controllers.

You can also modify the save game system. The classes that right now save data in the UAdventurePluginSaveGame class are the UQuestGraph, UInventory, UInventoryItem and UDialogGraphNode_Once classes. If you decide to persists the data in some other way, make sure to modify all of these classes to use your modified save game system.

# Tips, tricks and troubleshooting

Ensure that you never have references to classes that no longer exists. When playing in editor, the Game Instance is not recreated when launching a new game. So if your Item Manager exists on the Game Instance, you might face the following scenario:

* You start the game in editor.

* You stop playing in the editor.

* You modify and recompile an item.

* You start playing in editor.

If you do that, the Item Manager will still have references to a class that no longer exists (because you recompiled it), which causes all sorts of problems. The main sign of this problem is that you will start seeing classes with names beginning with the string "REINST_". This was just an example, be aware of this issue and try to avoid having references to classes that survive a PIE restart.

Try to package the game periodically and try to run the packaged builds. We encountered a few issues related to packaging when developing the game and they are usually difficult to debug. It is much easier to fix them if you know that some recent change caused a problem. If you encounter some packaging problems, we will probably not be able to help you, as the shipping process is done by Unreal Engine and is quite complex.

Whenever you must refer to an object using a TSubclassOf property or by an FName, try to create a customization that will allow the designers to choose the TSubclassOf from a picker with thumbnails and the FName from a combobox of valid values. It makes development a lot easier.

In general, you should always have your designers in mind. Choose carefully which methods should be exposed to blueprints and which are unnecessary. And if some common action requires too many steps, create a Blueprint Library method that will do those steps instead.

Unlike us, you know the game that you are making using our plugin. You can use this knowledge to modify the plugin to your game. Remove or hide properties and classes you do not need, add additional managers and controllers to your Game Context, create your own nodes that, for example, know whether the world is 2D or 3D. The UAdventureCharacter and UInventoryItem could contain references to the actors that represent them, though these properties would probably have to be filled by the actors when they’re spawned. And if you add a World Context Object to the Game Context, there is no limit to what your nodes can do.

