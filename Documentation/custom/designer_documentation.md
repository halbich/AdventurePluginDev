# Designer Documentation {#designer}

# Introduction

This document is meant as a guide for people who have never used the Adventure Plugin before. In the first chapter, which is the chapter you are reading right now, we will quickly summarize the documentation and what we think a reader should have done and should know before proceeding further. In the second chapter, we will explain some basic principles we followed when designing this plugin, so you know what our plugin can and cannot do, as well as some basic things universal to the entire plugin. Next three chapters will introduce the main three features of our plugin - Quest Editor, Inventory Item Blueprint and Dialog Editor. We will explain how to use these to design the flow of your adventure game. The chapter after that will explain how you can use the quests, items and dialogs you designed to actually build your game. In the last chapter of the document we will list some common problems and ways to solve them, as well as some general tips for developing games with this plugin.

## Requirements

We expect you have followed the Adventure Plugin Installation Guide packaged with the plugin that explains how to install Unreal Engine 4 and the plugin. We also expect that you went through the Time Lapsus Demo Documentation for a quick introduction to the plugin. For the purposes of this documentation it is not important which way of installing the plugin you chose. 

We also expect some basic familiarity with Unreal Engine 4. You do not need to be an expert, but you should be familiar with the editor, content browser and blueprints. If you are not, we recommend you go through the tutorials on this webpage: [https://docs.unrealengine.com/en-us/GettingStarted](https://docs.unrealengine.com/en-us/GettingStarted)

# Basics

Our plugin is meant to make creating adventure games easier. However, our goal here is not to make a complete toolkit that can do everything. There are still many things a programmer or a designer must do to work with this plugin. We focused mainly on making it easier to design the adventure game - the flow and the logic behind it. We identified three main areas that our plugin could help with: designing quests, items and dialogs. We will briefly describe the concepts here, though they will be thoroughly described in the following chapters.

Quests keep track of the player’s progress - what actions has she already taken, the values of game variables etc. But in most cases the quest does not control these variables in any way - a quest might have a flag "Talked with Potter" that should be true when the player has talked to the potter. But a dialog, blueprint or code must actually set that flag when the player talks to the potter, the quest will not set it automatically.

Item definition describes all the information about an item that is not specific to its representation in the scene. It defines e.g. its name or what happens when the player examines an item. But it does not define how will the object look when rendered in the scene or what buttons must the player click to trigger actions or combinations.

Dialogs describe communication between a player character (PC) and up to one non player character (NPC). Dialogs can show PC and NPC dialog lines, they support branching based on quest variables and quest flags, they allow the player to select dialog options, query which items are in inventory, put items to or remove items from the player’s inventory and a lot more. We also have our own class Adventure Character to identify characters involved in the dialog.

Dialogs, item definitions and quests do not work directly with the game scene. None of them are actors or widgets. To display anything to the player they use special presenter classes registered by designers. Some classes also define some event dispatchers, which can be used to notify actors in the scene when necessary. 

## Plugin configuration

When the plugin is enabled, you can configure some general settings that are applied to the entire plugin. If you click in the menu on Edit->Project Settings and then find Adventure Plugin in the list, you will be able to edit this configuration. It has these properties:

* Dialog/Inventory Default Presenter: These define classes that can show dialogs or the player inventory. You will want to modify these when you create your own presenters. The presenters will be described more in the Adventure Plugin Blueprints chapter.

* Default Dialog/Inventory Controller: These classes control the logic of dialogs and of the inventory. There is usually no reason for designers to modify these, as they just define some very simple logic, though there are some specific cases when you cannot avoid it. But as they are meant to be modified by programmers and programming knowledge is required to understand them, they will not be described in this document in more detail.

* Default Adventure Character/Item Manager: These classes can provide instances of Adventure Character and Item classes. Like controllers you probably do not need to modify these.

* Save Game: The type of class that stores the persistent data. It makes sense to create your own subclass of our Adventure Plugin Save Game, so you can store information specific to your game. Saving will be described in more detail later.

* Use Action Types: Here you can define all types of actions that the player can take, like Use, Read, Activate Mechanism etc. So for example, using a talking sword might be a Talk action, eating a meal might be an Eat action. The purpose behind these is to provide the player with visual indication of what action is she about to take. In our demo we change the cursor when over an object. The cursor then indicates what would happen on click.

# Quest

In adventure games the player usually has to do a number of actions. For example, to complete a level she might need to talk to some character, use some items, combine them etc. And often these actions must be taken in some order - for example, before stealing a key from a guard the player must first put the guard to sleep.

These actions and their prerequisites can be represented by a graph, in which the nodes are actions the player must take and the arrows between two nodes mean that the first action must be done before the other action can be completed. For example:

![](image_0.png)

This represents a very simple quest. It is obviously impossible to go to work without eating breakfast and drinking coffee. And you cannot buy coffee without your wallet and while not dressed.

Our plugin provides a very simple way to design these quests. A quest is an asset, so you will first need to find a place where you want your quest to be saved in the content browser. Once you find it, just right click in that place and select Adventure Plugin->Quest Graph

![](image_1.png)

This will create a new quest. Name it however you want and open it. You will see a graphical editor that already contains one node - END node. You can now create more nodes by right clicking anywhere in the empty space in the graph and selecting the node you wish to create. You can also create connections by dragging from the right side of one node to the left side of another node.

Right now there are these types of nodes:

* End node - There is only one node of this type. It is gray with a constant name END. 
It cannot be deleted, cannot be added, it is in every graph when created and it cannot have outgoing arrows. This node represents the end of the quest. Once all nodes that point directly to this node are true (i.e. the player did the represented actions), the quest is considered to be completed.

* Simple flag node - This node represents some action a player can take. It is yellow and it is possible to set it to true, signaling that the player did the represented action. But this flag will never set itself to true on its own - it must be explicitly set to true by code, dialog or by a blueprint script. You should set the Name property of this node, either by clicking the text field on the node while the node is selected, or by editing it in the properties pane when the node is selected. The name is visible in the graph and is also used to identify the node in dialogs, code and blueprint scripts.

* Picked up inventory item node - This node becomes true once the player picks up a specific inventory item. You can select the item in the Item property in the properties pane when you select this node. An important note - this only checks whether the player has at some point picked up the item, not whether she currently has it in inventory. This node is blue.

* Commentary - This node is purple and should serve no function whatsoever. It is meant to be just a note for designers and is considered to be true once all nodes that point directly to this node are true.

* Subquest node - This node is turquoise and represents another quest. The quest can be selected in properties pane once this node is selected. This node is true when the represented quest is true.

These are all the nodes that exists right now, but if you are missing some, programmers can easily add new ones.

In properties pane of every quest node you can also fill out the Location property. This has no functionality and exists only for designers. It specifies where the player is supposed to be when setting the flag.

You might have noticed that all of these nodes share one common property - once they are true, they can never become false again. That is done on purpose. Now if we ever get into a situation where a node is true and the nodes before it are false, we can safely say that it is a bug and we display a warning if not in a shipping build. It is also easy to find nodes that represent what the player should be able to do right now. You just need to find nodes that are false and whose previous nodes are true. 

The quest graph is a nice tool, but when designing you will often get into situations where you will want to keep track of some more complicated things. Because of that quests can also contain variables and events.

## Variables

Usually the game has to keep track of not only these significant quest flags, but also of many smaller ones - which doors are open, which items has the player already examined, what do the different characters think about a player etc. And other times, things might be simple, but reversible, e.g. if three switches need to be in a correct position before proceeding, we must track them, but we cannot use flags, as the player can set a switch from the correct position back to the incorrect position. And we cannot set a flag to false.

For these use cases we use variables. When no nodes are selected, you can see in the properties pane the following items: Bool Variables, Integer Variables and String Variables. Simply by clicking on the plus sign you can add a new variable to the quest, which can be accessed from blueprints, code and dialogs. You should always set a name for the variable, as well as its default value, i.e. what value will this variable have before something changes it. You can store three kinds of variables: booleans (True/False), integer and string (text) variables.

## Events

The last thing you can set on a quest are events. These are mainly used for communication between different parts of the game. For example, let’s say that as a part of a dialog a brawl should start. The dialog knows nothing about complex animations. However, it can fire event defined on a quest. Meanwhile, in the scene, some actor might be listening to the event. And once the dialog fires the event, the actor would start the brawl.

That is how events work - you declare them on a quest and then fire them, either through a blueprint, code or a dialog. If some code or a blueprint script is bound to that same event, it will automatically execute the appropriate code when the event is fired. But be careful - only one listener can be bound to a quest event at any given time. Once something else binds to that event, the old listener stops responding to it.

Events are added just like variables - deselect all nodes in a quest editor, click on the plus sign next to Quest Events in the properties pane and set a name for it.

## Tips and tricks

You might have realized that the way quests works, it is quite difficult to create dependencies between two quests, other than the simple case when another quest must be completely completed before progressing. While that might sound limiting, this was a design decision. The main advantage of using a graph to design a quest is that you can easily see how linear or nonlinear your game is. If you have quests that interact often, you should have them in the same graph. The quest does not need to correspond to what you would call a quest in an RPG game. A whole chapter might be represented by one quest.

One way you could organize your quests is to have one main quests, with all other quests being the subquests of the main quests, subquests of subquests etc. The main reason for this scheme is that once you start following it, it is quite easy for programmers to create a tool that will go through the main quest and its subquests and find all actions that the player can currently do. This is an excellent start for a hint system. 

Not all of your quests must have nodes and must correspond to some logical quests. Quests can also serve as a store for variables. For example, you could have a dummy quest called ItemStates, where you could store information about items - which items did the player examine etc.

An important thing about quests is that if using the normal plugin save game model, the variables and flags in these quests are automatically synchronized when saving and loading a game.

You might have noticed that you can set a name and tags for a quest. The name right now exists just to identify the quest in some other UI elements, though you can access it from code and blueprints at runtime for your own purposes. Tags exist purely for your own implementation, the plugin does not use them at all.

# Inventory Item

In most adventure games the player can pick up items, examine them, use them and combine them together. To specify the behavior of an item in one place, we created a new blueprint class Inventory Item. In this class you are meant to define everything about an item except for its visualization and behavior in the game scene. This limitation exists to allow flexibility. While different games might be 2D or 3D and while control schemes can be different in every game, in all adventure games the item will probably support some basic actions and have some common properties. 

Every Item Definition is a different blueprint class, so to create one, find the folder in the content browser where you want to create the item, right click and select Adventure Plugin->Inventory Item:

![](image_2.png)

Properties of an Inventory Item can be specified in the class defaults. Inventory Item’s behavior can be changed by overriding methods of the class. 

The basic properties defined on the Inventory item are:

* Name: Name of this item that can be shown to the player.

* Icon: Icon of this item, used as thumbnail of this item in editor. This property is accessible at runtime, so you can also use it to show the item’s icon in inventory.

* Item Tags: Designers can define different tags for the item. Right now the plugin does not use them in any way.

## Defining actions

You can also define the actions the player can do with the item and whether she can actually do them right now. There are several basic actions:

* Use: The player uses the item. This is a generic name for an action that might mean anything  - eating some food, using a mechanism, opening a box etc.

* Examine: The player examines an item. Usually this means that the player character describes the item, though you can also use this method to do something more complex, e.g. when examining a map, the map could be shown to the player.

* Adding the item to inventory and removing it from the inventory.

For all of these we can define whether the actions can actually be done by using either:

* Default Is Examinable/Usable/Pickable - Use these properties if the item is always either pickable, examinable or usable. So for example if the item can never be used, you would set IsUsable to false.

* IsExaminable/IsUsable/IsPickable methods - Override these methods when the item might become examinable, pickable or usable based on the game state. If you do not override these, the Default Is Examinable/Usable/Pickable are used. For example, an item might initially not be pickable because of a guard, but once the guard is put to sleep the item can be taken.

The rest of the properties and methods are specific to individual actions. For Use action we define:

* Use method: The method that is executed when the player actually triggers the use action. If you do not override it, the use action does nothing.

* Use Action Name: This is the name of the action that can be displayed to the player, so she knows what the action will do before starting it. For example, when using a locked safe, the action name could be "Open safe".

* Use Action Type: Use action can also have a type specified, for example using a talking sword might be a talk action. The possible types are loaded from plugin configuration, which was described in the Plugin Configuration chapter..

For examine action we define:

* Examine Dialog: As examining an item often means starting a dialog, here you can define the dialog and the entry point from which the dialog should start. Entry points and dialogs will be explained in the Dialog chapter.

* Examine method: You can override this method to do something different than starting a dialog when the item is examined. If you do, the Examine Dialog variable is ignored, though you can of course still use it in your overridden method.

The item does not actually have methods that can remove or add items. InventoryController, a class that will be described later, is responsible for that. However, you can still have your own behavior for when that happens by either:

* Overriding the On Removed From Inventory/On Added To Inventory methods.

* Or by binding to the Removed From Inventory/Added To Inventory event dispatchers. These dispatchers are public, so you can bind to them from outside of the item as well.

## Item State

We assume that an item can be in one of the following states:

* Not Spawned: The item does not exist yet.

* Spawned: The item exists in the scene.

* In Inventory: The item is in the player’s inventory.

* Used: The item was in the player’s inventory, but is there no longer, it was used in some way.

* Custom: Items in this state are in a state that is unique for your game. The plugin will then not change the state automatically when adding the item to or removing it from the inventory.

* Invalid: You should never see this in runtime, this exists just to handle error states.

The Inventory Item has these properties and methods related to item states:

* Default Item State: The state in which the item should be when the game starts. Note that if you set the default item state to In Inventory, the item will not add itself automatically to the inventory, the designer still has to do that manually.

* Get Item State/Set Item State methods: These methods can modify and retrieve an item state at runtime.

* Was Picked Up method: This method is used to check whether the item was ever picked up. This method is used by quests. If you do not provide your own implementation, this method returns true if the item is not in the Not Spawned or Spawned state. You should override it when using Custom states or when the the player can put an item back into the scene, setting the state to Spawned State, even though the item was already picked up.

* Item State Changed event dispatcher: This event dispatcher is fired when an item state changes.

Note that the plugin changes the state automatically to In Inventory when an item is picked up and to Used when it is removed from inventory. This automatic state change does not happen if the state is Custom, as we cannot know what the custom state means and whether we should do anything or not.

## Combinations

First, note that everything in this section applies also to the the Adventure Character class, which is described later on.

In adventure games it is common that a player can combine two items together to produce some results. For example, she can combine a key with a locked chest to open the chest, or two parts of a broken item to fix it. It is also common that NPCs respond to items being used on them. Our plugin simplifies the process of defining which combinations are possible.

Both the Inventory Item and the Adventure Character class have an overridable function called Init Combinations. This method is automatically called by the plugin before the class is used and is the method in which you should register all combinations for this class. If you register combinations anywhere else it will cause a warning.

Each combination is represented by a combination object. Combination object is any object implementing the Combination Interface, which defines everything important about a combination. The plugin provides 3 types of combinations. For all of them you define a single item or character with which the combination works, the name of the combination that can be displayed to the player and its use type (see the Plugin Configuration chapter for more details). They specify combinations between the current item or character and one specific target object. They differ in the action that happens when the combination is triggered, i.e. when the player actually combines the two items. You can create these combinations using these methods:

* Create Dialog Combination with Single Item: This creates a combination that, when triggered, starts a specific dialog.

* Create Simple Combination with Single Item: This creates a combination that, when triggered, removes both combined objects from the inventory if possible (i.e. if the items are actually in the inventory) and replaces them with another item.

* Create Generic Combination with Single Item: This creates a combination that, when triggered, calls the event specified by an argument of this method. That event can do anything.

Once you create a combination object, call the Add Combination Object to register it for this class. All combinations work both ways, i.e. if there is a combination A+B, B+A does the same thing. If you specify a combination A + B on one object and B+A on the other, it is considered to be an error and the behavior in game will be undefined. Same thing will happen if you have multiple valid combinations between A and B registered on object A.

When you are done creating combinations, you can press compile and notice that both on this object and on the target object of the combination, read only class defaults properties Local Combinations and External Blueprint Combinations got filled. In these fields you can see all combinations involving this object. These exist only for debugging, you cannot access these during runtime. Note the external combinations show only blueprint combinations. Technically it is possible to create your own inventory items in C++. If you do, combinations will work, but will not be visible in the External Blueprint Combinations list.

If you require some combinations not provided by the plugin, for example combinations that work with tags, both designers and programmers can create their own combination objects and add them in the Init Combinations method. Just create a class that implements the Combination Interface. The interface has following methods:

* Can Combine With: This method returns true if it is possible to combine the two given items.

* Execute: Does the action this combination represents.

* Get Combination Target Classes: This method returns all classes with which this item could be combined.

* Get Name: Returns the name of this combination that can be shown to the player.

* Get Debug Name: Returns the name to be shown in editor for this combination.

* Get Use Action Type: Returns the type of this combination, see the chapter Project Configuration for more details.

## Tips and tricks

You might have noticed that since each item is defined by a class, it is not possible to have more instances of a single class in inventory. But since the items support inheritance, it is not a problem if you know how many of those items will you need. Let us say that you need 4 pieces of a broken map and you want them to behave identically. Just create Map Piece class defining every map piece and then create its subclasses Map Piece 1, Map Piece 2, Map Piece 3 and Map Piece 4.

You can also use inheritance to add common behavior to items. Let us say you have multiple sharp items that you could pick up and that you could also have a dog in your inventory. And you would want your character to protest when the player tries to combine a sharp object with the dog. You would just need to give the sharp items a common ancestor, class Sharp Item inheriting from Inventory Item. The Sharp Item class could register the combination with the dog and the combination would be applied for all child items.

You can also easily extend the Inventory Item class yourself. Let us say that you are making an old school adventure game, with actions like Eat, Push, Pull etc. You could create your own subclass of Inventory Item where you could define all of these actions just like we define Use action right now. After that you would just have to create your inventory items by creating blueprints inheriting from that custom class, instead of inheriting from the Inventory Item class directly.

# Dialog 

Our plugin also makes designing dialogues easier. To support dialogs we created two types of assets - Adventure Character and Dialog Graph - which will be introduced in this chapter.

## Adventure Character

For every character that can talk in a dialog, you should create a custom Adventure Character class. You can create that class in content browser by right clicking and selecting 
Adventure Plugin->Adventure Character.

![](image_3.png)

As with all other classes that are a part in the plugin, this class cannot be inserted into the scene and can communicate with objects in scene only indirectly. The class defaults of Adventure character class define properties relevant to dialogs, as well as a very simple animation system. The properties are :

* Name: The name of this character. It is localized, so you can use it also in dialog UI.

* Is Player character: This boolean is true if this character represents a player character, otherwise it represents an NPC character.

* Icon: An image representing this character. It is used to define this character’s image in the content browser. But it is also available at runtime, so it can be used as an image in dialog UI.

* Then we have properties Is Animatable, Animation States, Talking Animation States and Default Talking Animation State. These are part of the animation system described further in this chapter.

The Adventure Character also supports combinations with items. Those are described in the Inventory Item chapter.

### Animation system

We have implemented a very simple animation system for our plugin, to allow dialogs to play animations on characters. The dialog might make a character play an angry animation when discussing something, or it could make a character react in shock to what the other character did or said.

For these use cases, you can define animation states on the Adventure Character class. Animation state is an animation that can be played either once or in a loop. Animations are defined by these properties:

* Is Animatable: If false, the animation system is inactive and all animation calls are ignored.

* Animation States: This array contains names of all possible animations of this character.

* Talking Animation States: This should be a subset of Animation States. It defines all animations that can be played while a character is talking.

* Default Talking Animation State: This should be from Talking Animation States, specifies the talking animation that should be played if no animation was specified.

When playing an animation, the Adventure Character class does not play animations itself. It raises events that actors on scene are expected to bind to.

## Dialog Graphs

Now that you have the characters that can talk to each other, you can start designing the flow of the dialog. We use Dialog Graphs for that purpose. Each Dialog Graph contains a conversation between up to two characters. By that we mean that a graph can also contain a monologue, for example a character can be describing an object or have a soliloquy.

Each Dialog Graph is an asset. To create it, find the folder where you want to create it in the content browser, then right click and select Adventure Plugin->Dialog Graph:

![](image_4.png)

The Dialog Graph editor looks quite similar to the Quest Editor. It also has a large space for designing the graph and a property pane. Before going into all different things you can insert into the graph, let’s first focus on the property pane. If you have no nodes selected, you will see the properties for the entire Dialog Graph. The most important properties here are Player Character and NPC Character. Here you can set which two characters are talking in this dialog. It is expected that if you do not fill the NPC Character, this graph represents a monologue. You can also specify the graph name and tags here. They are not used anywhere, but are accessible from scripts and code.

Now we can focus on the dialog graph itself. In every graph you can see a Main Entry Point node. That node always exists in a graph and cannot be deleted. But you can create many more nodes by right clicking in the graph and selecting the node you wish to add, or by dragging from the bottom of an existing node that has at least one output (i.e. dialog can continue after this node). You can connect these nodes by arrows. Arrows specify the flow of a dialogue. When you play this dialog, it is started from some specific node. When a node is executed, i.e. the action the node represents is completed, the arrow specifies which node should be executed next. You can have multiple outputs for a node - that means that the next node will be based on some condition or on player input.

Here is a short example:

![](image_5.png)

This is a part of a graph that defines a very simple dialog. You should always read the dialog from top to bottom. In this example, the grey node will first check the Sell vase variable on the Main Quest. Based on that variable it will display one line or the other. You can of course chain these nodes to create much more complex dialogs, see the demo for more examples.

Some nodes have some specific properties you can set in the property pane. But for every node you can set an ID, which should uniquely identify the node. You do not have to set the ID if you never refer to that specific node by ID. You can also specify a note for each node. This note will be displayed in the node and serve as a commentary, for example specifying the intended tone of the dialog line.

### Dialog node types

Right now the plugin supports these types of nodes:

* Dialog Lines. These are the main building blocks of dialogs. When this node is encountered when the dialog graph is executed, a dialog line should be played. And once it is complete it should go to the next node. There are two main node types - Dialog Player Line and NPC Player Line. These have the exact same properties, but the first one is a line said by the player, whereas the second one is a line said by an NPC. There is also Dialog Player Line Option. This node is a stripped down version of the Dialog Player Line, which should be used if a line should be presented as a dialog option, yet never spoken aloud. Dialog lines have these properties:

    * Talking Animation: Defines the animation that should be played while the character is speaking. If not defined, the Default talking animation of the character will be used. 

    * Dialog Text: The text that should be displayed as the text for this dialog line, whether in subtitles or as a dialog option.

    * Option Text: When not empty, this overrides Dialog Text as the text to be presented to the player when choosing dialog options. This is the only property that exists for Dialog Player Line Option.

    * Dialog Sound: The text that should be played for this dialog line.

    * Skippable: If true, the player should be able to skip this dialog line

    * Text Duration: This is used only if Dialog Sound is null. Defines how long should the dialog line stay on the screen. If it is 0, it will stay on the screen indefinitely.

* Branching. It is common that the dialog might take different paths based on various factors. For example, if in the past the player helped an NPC, that NPC could say different things to express gratitude. For all of these branching nodes you specify a condition. The node has two output pins, i.e. the node has two output arrows (or three when comparing integers). When the node is visited during execution, the next node is chosen based on whether the condition was true or false. We now support these kinds of conditions:

    * Branch on bool variable: For this node you need to define the boolean variable it points to. The node chooses the True pin if that variable is true.

    * Branch on bool variable equality with a variable: For this node you need to define two boolean variables. And the node is true if those variables have the same value.

    * Branch on integer variable comparison with a constant: For this node you need to specify an integer variable on a quest and a constant. The node has three output pins, one for when the variable is less than the constant, one for when it is more and one for when they are equal.

    * Branch on integer variable comparison with a variable: Just like the above, but the variable is compared with another variable.

    * Branch on string variable: For this node you need to specify a string variable on a quest and a constant string. The node chooses the True pin if these variable is equal to the constant string.

    * Branch on string variable equality with a variable: Like above, but for comparing the string variable with another string variable.

    * Branch on item in inventory: For this node you need to select an inventory item. The node chooses the True pin if that item is in the player’s inventory.

    * Branch on Quest flag: For this node you need to specify a simple flag on a quest. The node chooses the True pin if that flag is set.

    * Branch on quest completion: For this node you need to specify a quest. The node chooses the True pin if that quest is completed.

    * Once: This node is different from the others. It initially chooses the True pin. However, after the first time this node is executed, it will always choose the False pin. This node automatically serializes its state into a save file if using our default save game system.

* Options: This node is a bit more complex. When it is visited, it should give the player a list options. And the option the player will select will specify which node will be executed next. This node has many unique features:

    * You can use the plus and minus sign on the node to specify how many options should be presented to the player. When you click on these buttons, more output pins will be created. This allows you to have an ordered list of options specified. 

    * This node also supports branching. This allows the designer to offer the player different options based on her choices. When a child of the option node is something else than a Player Line or a Player Line Option, we check the next node of that node. And so on and so forth until we either find the node we are looking for or until we find the end of a graph. If no such node is found, this option is ignored.

    * When searching for player options, the nodes are not actually visited. We just check what would be the next node of that node without executing it. So for example, if you had a node adding an item to the inventory on a path to a Player Line, that item would not be added to the inventory unless that Player Line was actually selected. Important consequence of this is that when there is a Once node in the path to the Player Line, it will still be true until the first time that Player Line is chosen.

    * We highly recommend to only put branching nodes between the options node and the Player Lines. This will make the graph a lot more readable.

    * The options node also has a fallback pin, marked FB. The arrow from this pin is followed if no valid options to present to the player were found.

* Entry points: The Main Entry Point exists by default, but the designer can add Secondary Entry Points. All entry points work the same, they mark the places where the dialog can be started from code or blueprints. They cannot have input pins, they can only start a dialog. For Secondary Entry Points you should always set the ID, as it is used to identify the Entry Point from which the dialog can be started.

* Goto. For this node you must specify the ID of the target node. That node is considered to be the next node to be executed after this node, just like if there was an arrow connecting the Goto node and the target node.

* Event: For this node you must specify an event on a quest. When this node is visited, that event is fired. Note that if some long running task is launched from that event, e.g. showing a dialog, this node will not wait and will continue visiting other nodes immediately. Normal use case of this node is to do things you cannot do in this graph, like starting a cutscene, changing a level or changing weather.

* Data manipulation. You can also change variables in a quest from a graph. There are multiple nodes that can do this.

    * One can set a string variable on a quest to a constant string value.

    * One can set a boolean variable on a quest to a constant boolean value.

    * One can set an integer variable on a quest to a constant integer value. 

    * One can increment an integer variable on a quest.

    * One can switch a boolean variable to the opposite value, i.e. true to false and false to true.

    * One can set a simple quest flag.

* Item manipulation. There are Add to Inventory and Remove from Inventory nodes that can add or remove items from the player’s inventory.

* Animations: These can play an animation for either the PC or an NPC. There are three kinds of these nodes:

    * Play PC/NPC animation once: These nodes play an animation once, wait until it is finished and then they continue with the next node.

    * Set PC/NPC animation state: This changes the animation state of the character until something else changes it. It is important to note here that a dialog line also changes and then resets the animation state.

    * Reset PC/NPC animation state: This resets the animation state set by Set PC/NPC animation state and gives control back to the actor.

* Save state: If using the default save game system, this will save the current save game data to the disk. You can use this e.g. when after a dialog line that was meant to be a checkpoint.

* Exit. This node does nothing, but is used to mark an end of a dialog. Use in complex graphs, so you know where the graph can end.

* Comment. This node does nothing and exists solely to help designers. It contains a text that is shown in the node.

These are all the nodes this plugin currently supports. You can link these nodes to create many interesting dialogs. And if there is some type of node that could be useful for your project but does not exist, programmers can easily create new nodes based on the needs of your project.

## Tips and tricks

Sometimes you might want to wait for some things the graph doesn’t support. For example, you might want to trigger an animation sequence and continue the graph after that sequence. The only way to do that right now is to fire an event doing that task, end the graph, i.e. not giving the Event node any children, and creating a new entry point. The blueprint handling that event must then start the dialog again from that entry point.

When creating a new Dialog Graph and only one player character exists in the entire game, i.e. only one Adventure Character with Is Player Character set to true, the Player Character on the new graph is automatically set to the only player character.

While we use the terms Player Character and NPC, there is nothing stopping you from creating a dialog between two NPCs. We just use these terms to differentiate between the two speakers.

Think carefully about how you want do organize your graphs. For example, you will probably need to create dialog graphs for item descriptions. However, it might be unnecessary to have a separate graph for every single item. You might decide it makes more sense to create a single graph for all item descriptions. But it might also make sense to create a graph for every item if, for example, there is a unique line for every invalid combination you can do with the item.

# Adventure Plugin Blueprints

In this chapter we will describe how to actually use those Dialog Graphs, Inventory Item Blueprints and Quest Graphs so that they actually do something. First we must introduce the central class - the Game Context.

## Adventure Plugin Game Context

The Game Context is an object that provides access to all Adventure Plugin functionality. All of our methods need it and take it as an argument, so to do anything you will also need to retrieve a Game Context. Fortunately there is a very simple way to do that - If your Game Instance inherits from AdventurePluginGameInstance, you can just call this method from blueprints:

* Get Current Game Context: This method will retrieve a game context that will use the plugin configuration to determine which presenters and controllers to use.

You can change which Game Instance your project uses in the Project settings, section 
Maps & Modes. The presenters and controllers are also specified in project settings, see the Plugin Configuration chapter.

You can also create your own game context. There are two main use cases why you would want that:

* Your Game Instance does not inherit from AdventurePluginGameInstance and you cannot or do not want to change that.

* You want to have multiple Game Contexts for different situation. For example, let us say that you want to implement background conversations, that you would want characters speaking on their own. To do that, you would probably need a different dialog presenter - the dialog UI would not be visible and player’s controls would not be restricted as in a regular dialog. And if you wanted to show multiple dialogs at once, you would need multiple instances of the Dialog Controller class, as one dialog controller can only show one dialog at a time. So you would have one context for background conversation and one context to be used normally.

Now we will describe how to create your own Dialog Context. If you plan to use the default one, you can skip this and go to the next chapter.

Creating a Game Context is easy - just construct a new instance of the AdventurePluginGameContext class. Now you have an empty context. You need to populate its variables before using it. Except for presenters, you will probably just want to fill them with instances of our implementations of these classes, as you are unlikely to need modification of the default behaviors. But if you need, to, you can create your own implementations, though we recommend that these modifications should be done by programmers. These are the variables you need to set:

* Adventure Character Manager: This class can convert an Adventure Character class reference to its instance. All of your game contexts must use the same instance of the Adventure Character Manager class. 

* Dialog Controller: This class is responsible for controlling the flow of a dialog. Each Dialog Controller can only play one dialog at a time. This means that if you need multiple dialogs playing at once, you need different Game Contexts with different instances of the Dialog Controller class.

* Dialog Presenter: This class is responsible for actually playing dialog lines and playing animations. It is likely that you will need custom presenters. The presenters will be introduced later, right now it is important to note that each instance of a Dialog Controller should be paired with its own instance of a Dialog Presenter, as having a single presenter for multiple concurrently running dialogs would likely cause problems.

* Save Game: This is the class that contains all data that should be persisted on save game. All of your game contexts must use the same instance of the Save Game class. You might want to add your custom implementation here, so you can save things like player location and in general things that are not stored in quests. The Save Game must inherit from AdventurePluginSaveGame.

* Inventory Controller: This class manages the player inventory and can tell a presenter to show or hide inventory. You might want to use multiple instances if you have multiple player characters that can have their own inventories, or if you wanted to have inventories for NPCs or containers. Though for that you would need support from programmers, as creating multiple inventories is not as easy as just creating a new Inventory Controller. The problems are described in the Programming Documentation in more detail.

* Inventory Presenter: This class can show and hide inventory to the player. It is expected that you will create your own presenter to customize your UI. You might need more than one presenter if you decided to, for example, use inventory for containers like in RPG games.

* Inventory Item Manager: This class can convert an Inventory Item class reference to its instance. All of your game contexts must use the same instance of the Inventory Item Manager class.

You can quickly check if a game context is valid by calling the Is Game Context Valid method. Note that if you create your own game contexts, you are also responsible for their management. It might make sense to store them on the Game Instance, so you do not have to recreate them every time they are required.

## Custom Dialog Presenter

A Dialog Presenter is any blueprint class implementing the Dialog Presenter Interface. It must implement the following methods:

* Set Presenter Visibility: This is called when the the dialog starts and ends. It should either show the presenter if the Visible parameter is true or hide it if the Visible parameter is false. Use this method to display or hide dialog related UI.

* Show Dialog Line: This method displays a dialog line to the player. Has two arguments. Dialog Line Data is a struct containing all information about the dialog line. Break it and use it to display the dialog. The arguments are described in the Dialog chapter, they are the same ones as the properties of the Player Line graph node. The other argument is a Dialog Controller. That is the controller that called this method. Once the dialog line finishes, the presenter must call the Show Dialog Line Callback method on the controller, to notify the controller that it should move on to the next node in the graph.

* Show Dialog Selection: This method should show the player a list of options to select from. Receives two arguments. The Options method is the array of all options to present to the player. It is a list of Dialog Line Data structs, the property on that struct Option Text is the string that should be displayed to the player as the option. The other argument is the Dialog Controller, which is the controller that called this method. Once the player selects a dialog option, you should call the Show Dialog Line Selection Callback, with the index of the selected node passed as an argument.

* Play Animation Once/Set Animation State/Reset Animation State: The presenter should to do something regarding animations. Animation Target is the object being animated, Animation Name is the animation that should be played and Dialog Controller is the controller that initiated this called. The animation system will be described in more detail later. For now:

    * Play Animation Once should play the animation once and once it is done it should call the Play Animation Callback method on the controller, passing the Animation Name it received and the information about whether the animation completed successfully

    * Set Animation State: The animation target should now play the specified animation in the loop.

    * Reset Animation State: The animation target should stop playing the animation it is playing.

Once all of these methods are implemented, the presenter is ready for use. If there is anything unclear, just check the implementation in the demo to see a working presenter.

## Custom Inventory Presenter

Inventory Presenter is any class that implements the Inventory Presenter Interface. The presenter must implement these methods:

* Show Inventory: The presenter should display the specified inventory. Call the Get Items method on the Inventory to get a list of items to display. 

* Hide Inventory: The presenter should hide the specified inventory.

The presenter is expected to respond to the changes in the Inventory. It is expected to bind to the Inventory Changed event dispatcher, which is fired anytime the inventory is modified. It can also bind to Added to Inventory/Removed from Inventory event dispatchers defined on items themselves if it needs to.

The presenter will probably also be responsible for calling the Examine and Use actions on objects in inventory based on the player’s input, as well as handling the combinations between two items and combinations between the item and a character.

## Important Blueprint Functions

Now that you understand the most important concepts, we can introduce all of the other functions you can use to interact with the plugin data and use its functionality. We do not introduce all of the functions, we introduce only the high level ones. For example, there is a function to start a dialog based on a dialog definition. You could also get your game context, retrieve the dialog controller and start that dialog from there. We will not describe the second approach, just the first one. If you need to, included with the plugin is a reference documentation for all blueprint nodes exposed by this plugin. You can browse it for details.

Also, all of our functions are documented, so if you ever forget what a blueprint method does or what parameters it requires, just create it and you will see the documentation when having the cursor over the node or the individual parameters.

It is also important to note that all of our methods immediately check whether all of their input are valid. If something is invalid, the node logs an error and does nothing else.

### Getting Adventure Character/ Inventory Item instances

When we defined Inventory Items and Adventure Characters, we mentioned that they are blueprint classes. What that means is that unlike Dialog Graphs, their instances are not managed by the engine. When designing the game, you will often work with a class references for items and characters, as those can be selected from a list of all classes. But our plugin works with actual instances of these items. To retrieve them, we expose two methods:

* Get Item: Retrieves an instance of the specified Inventory Item class.

* Get Adventure Character: Retrieves an instance of the specified Adventure character class.

Always use these methods to retrieve the instances, never create instances by, for example, calling Construct Objects methods. There should always be only one instance of each class, otherwise the plugin will stop working correctly.

### Show Dialog

You can start a dialog either from the main entry point or from an entry point you define. To get the Dialog Graph Entry point that you need, create a variable of that type on the blueprint object you are modifying. After compiling the blueprint, you will be able to select the dialog and an entry point from the list of entry points defined on that dialog. It should look like this:

![](image_6.png)

To start a dialog, you need to call one of these methods:

* Show Dialog from Entry Point: Starts the specified dialog from the specified entry point.

* Show Dialog: Starts the specified dialog from the main entry point.

These methods do not wait until the dialog actually finishes, they return right away.

### Inventory manipulation

To show or hide the inventory, call one of these methods:

* Show Inventory: Shows the default inventory.

* Hide Inventory: Hides the default inventory.

* Set Inventory Visibility: Has a parameter Visible. If true, it works like Show Inventory. If false, it works like Hide Inventory.

To manipulate the inventory contents, you must get a reference to the inventory by calling the Get Inventory method on the Inventory Manager object on the Game Context. Once you have the reference, you can call the following methods on the Inventory object:

* Add Item: Adds the specified item to the inventory.

* Remove Item: Removes the specified item from the inventory.

* Has Item: Returns true if the specified object is in inventory.

* Get Items: Returns the list of items currently in the inventory.

* Set Items: Sets the list of items currently in the inventory. Be careful when using this method, as it does not fire notifications. It is meant to replace the entire inventory with a different one, for example when changing chapters.

* Begin Update: Sometimes you might be making more updates in a row, for example when combining items, you might be removing two items and adding another one at the same time. In those cases you should call this method. If you do, Inventory Changed notifications will be temporarily suspended until you call End Update, so the presenter is not flooded with the notifications.

* End Update: Call only after calling Begin Update. Stops suspending notifications and creates a notification with the list of all changes suspended since the Begin Update call. 

For your convenience, the most common operations on the inventory are accessible through global blueprint functions. They only serves as shortcuts for the process described above. Those functions are:

* Add Item to Inventory

* Remove Item from Inventory

* Has Item in Inventory

### Items

If you get a reference to an item, either through inventory or by calling Get Item, you can call the methods described in the Inventory Item chapter.

### Quests

These methods are defined on the quest object:

* Is Complete: Returns true if the quest was completed.

* Get FullfilableNodes: Returns the list of nodes that can be set true, but are not, i.e. their predecessors are true, but they themselves are not.

To work with quest variables, flags and events, you will first need a way of identifying them. For each type of variable there exists a structure like Quest Graph Flag or Quest Graph Bool. That structure uniquely identifies the desired variable. To define it, create variable of that type on some object and compile the class. You should now see a custom picker for that variable which allows you to select a quest and the variable in that quest you want to work with. It should look something like this:

![](image_7.png)

Once you have that, you can use the following methods:

* Get Quest Bool: Retrieves the value of a quest bool property. Requires Quest Graph Bool structure to identify the variable.

* Set Quest Bool: Sets the value of a quest bool property. Requires Quest Graph Bool structure to identify the variable.

* Get Quest Flag: Retrieves the value of the specified simple flag. Requires Quest Graph Flag structure to identify the flag.

* Set Quest Flag: Sets the the specified flag to true. Requires Quest Graph Flag structure to identify the flag.

* Get Quest Integer: Retrieves the value of a quest integer property. Requires Quest Graph Integer structure to identify the variable.

* Set Quest Integer: Sets the value of a quest integer property. Requires Quest Graph Integer structure to identify the variable.

* Get Quest String: Retrieves the value of a quest string property. Requires Quest Graph String structure to identify the variable.

* Set Quest String: Sets the value of a quest string property. Requires Quest Graph String structure to identify the variable.

* Bind Quest Event: Registers a handler for the specified event. If there already was an event registered for that event, the old event handler is removed and the new one is used instead. Requires Quest Graph Event structure to identify the event.

* Fire Quest Event: Executes the handler for the specified event. Requires Quest Graph Event structure to identify the event.

### Combinations

Blueprint methods to create combinations were already mentioned in the Inventory Item chapter.

To interact with them during the game you can use the following methods on both Inventory Items and on Adventure Character objects:

* Get Combination with Object: You need to pass another Inventory Item or Adventure Character as an input parameter. If a combination exists between these two objects, it is returned. Otherwise it returns an empty object. Note that while you can call any methods on the interface, you should not call the Execute method directly. Call it using the Execute Combination on this object. But you can freely query the combination object you received to get its name and type.

* Try Combine With: You need to pass another Inventory Item or Adventure Character as an input parameter. If an combination exists between these two items, it is executed. Returns true if a combination was found and executed, otherwise false.

* Execute Combination: You need to pass another Inventory Item or Adventure as an input parameter, as well as the combination you want to execute. Executes the combination.

## Animation System

We created a very simple animation system for the purposes of the plugin. We already mentioned some of it in the Dialog chapter, but we will repeat it here so everything is in one place.

The Adventure Character class implements the Animatable Object Interface, which has these methods:

* Play Animation: The object should play the specified animation once, calling a callback once it is done.

* Set Animation State: The object should play the specified animation in a loop.

* Reset Animation State: The object should stop playing the animation it is playing. The object is now expected to play its idle animation.

* Get All Animation States: Retrieves the list of all animations supported by this object.

* Get Talking Animation States: Retrieves the list of all animations that can be played while speaking, different emotions like anger etc. Should be a subset of Get All Animation States.

* Get Default Talking Animation State: Retrieves the talking animation that should be used if none other is specified.

The Adventure Character class implements the Get All Animation States, Get Talking Animation States and Get Default Talking Animation State using constants, which is quite simple. However, as the class does not exist in the scene, it cannot play animations itself. It instead exposes the following event dispatchers:

* Play Animation Once Event

* Set Animation State Event

* Reset Animation State Event

These event dispatchers are fired when the corresponding interface method is called. The object on the scene is then expected to change its animation state accordingly. Also, as the Play Animation Once interface method has a callback, once the object on the scene finishes playing the animation it should call the Animation Finished method on the Adventure Character, so the Adventure Character can call the callback it received in the Play Animation Once method.

## Save/Load System

All of our classes store their persistent data in the Save Game object on the game context. In the default game context a save game is already present, but you can create your own. Just make sure that all game contexts use the same Save Game object.

To create a Save, call the Create Save method. This method requires a name of the save and a user index. The name is up to the designer. User Index is required only on some platforms and is the master user index used to identify the user doing the saving. It is not needed on PC, which means it is not covered by this documentation.

Once you have a save, saving is as easy as calling the Save method on the Save Game object on the Game Context.

To load the game, call the blueprint function Load Game from Slot, with the Slot Name and User Index you used to create the game. Cast the returned object to Adventure Plugin Save Game, replace the save game on the Game Context and reload the level. As all plugin objects store persistent data directly in the save game object, this should be enough to load the state of the game.

If you want to store your own data in the save game objects, like actor position, orientation or the current level, there are three ways to do it:

* Create a special quest for this information and store everything there. This approach is easy, but not very flexible.

* Add your own data to the save game objects using the blueprint methods on the object. You have to make sure that you never create collisions, as data in the save game is saved by simple string identification. Collision with the plugin data is unlikely, as we store everything either by generated unique IDs or by a long string that includes full path to the quest asset. But be careful not to create collisions between your own objects. The methods on the save game object are:

    * Get Bool or Default: Return a boolean variable or the default value passed as a parameter if that variable was not yet stored.

    * Get Int or Default: Return an integer variable or a default value passed as a parameter if that variable was not yet stored.

    * Get Item State Or Default: Retrieve the item state of an item or a default value passed as a parameter if that item’s state was not yet stored.

    * Get String or Default: Retrieve a string variable or the default value passed as a parameter if that variable was not yet stored.

    * Set Bool: Sets the value of a boolean property.

    * Set Int: Sets the value of a boolean property.

    * Set Item State: Sets the state of an item.

    * Set String: Sets the value of a string property.

* You can subclass the Adventure Plugin Save Game object and give it your own properties. If you do this, make sure that you change the type of the Save Game property in the configuration, see the chapter Plugin Configuration. If you change the configuration, the Create Save method will create an object of the correct type.

# Tips, Tricks and Troubleshooting

In this chapter you will find miscellaneous information that did not fit into any other chapter, as well as some common problems and solutions for them.

When packaging the project, make sure you are not using the Blueprint Compilation Manager. You can find this in the Project Settings->Editor->Blueprints->Use Compilation Manager. There is a bug in compilation manager that causes errors when making shipping builds.

The plugin was designed to be extensible. If you find any functionality that is missing, any programmer familiar with Unreal Engine 4 should be able to implement the missing features.

All text that is meant to be shown to the player is localizable. You can use Unreal Engine’s Localization Dashboard for localization. Right now the game does not support localization of audio assets.

While the plugin was made with adventure games in mind, there is nothing stopping you from using this plugin with other genres, like RPGs and FPS games. In our opinion the most useful part of this plugin is the Dialog Graph editor, which can be used in all kinds of games.

Everywhere where comboboxes are used for our plugin specific things - quest variables, animations, use action types etc. - the combo boxes only make it easier to find the correct name of the property. They do not bind in any way to that property. So if, for example, you rename a variable on a quest, you will also have to find all references to that variable and rename them as well.

When preparing your actual game for development, create first the generic blueprints - a blueprint for an item on the screen, a blueprint for a character on the screen, presenters, UI widgets etc. This way it might take it a bit longer to get started, but the subsequent development will be much faster. Feel free to use the blueprint classes included in the template and modify them for your needs.

If using a custom Game Instance, make sure you recreate all of its objects when restarting the game in editor. There is a bug in the engine that can appear if you play the game in editor, stop playing, modify an item or a character, compile it and start playing again without recreating the Adventure Character Manager and the Item Manager objects.

Dialogs are powerful. If, for example, a combination should remove an item from the inventory and launch a dialog, you could create a dialog that removes the item and then proceeds with the dialog, so you can use the dialog combination instead of having to create a complex generic combination.

