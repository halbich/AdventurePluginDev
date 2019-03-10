# Time Lapsus Demo Documentation {#demo}

# Introduction

This document describes the Time Lapsus demo. It covers both gameplay and technical aspects of the project. This document also serves as an introduction for people who wish to understand the Adventure Plugin, the technology used under the hood.

This document will first introduce the demo from the gameplay point of view - how to play it. That chapter will also include a walkthrough. Then, in the next chapter, we will introduce the demo from the technical side.

## Requirements

The packaged demo requires a machine with Windows 10 64-bit installed. 

The Unreal Engine project requires Unreal Engine 4.19.2 to be installed, see the Adventure Plugin Installation Guide for details.

Any machine capable of running the Unreal Engine 4 should also be capable of running the packaged demo.

# Gameplay Guide

To run the project, open the .exe {PluginPackageDir}\Demo\Binary\TimeLapsusDemo.exe, where PluginPackageDir is the folder where you extracted the plugin package.

Main game menu should appear. Here you can select the game language by clicking on the flags in the top left corner on the screen. This guide is in english, so english names will be used for the UI elements in this documentation.

There are three buttons in the menu:

* New Game: This will start a new game from the beginning. You will first need to select one of the three save game slots the new game will use.

* Load Game: This will load a previously loaded save game. Only save slots that contain data can be clicked.

* Quit: This will close the game.

So when running the game for the first time, you should click on New Game.

## How to Play

The player character has found magical glasses which allow him to see things that no one else can. And using these, he sees that across the river on the hill is the Holy Grail. The character wants it, but, unfortunately, there is a chasm preventing our hero from just going to it. Can you help the hero find a way across?

The game is a point and click 2D adventure game. So you only need mouse to play it. When your mouse is over an object with which you can interact, the cursor will change to indicate what will happen on click. These are the cursors that can appear:

![](ico_0.png) - The character will walk to the cursor.

![](ico_1.png) - The character will enter the building under the cursor.

![](ico_2.png) - The character will start a conversation with the character under the cursor.

![](ico_3.png) - The character will try to pick up the item under the cursor.

![](ico_4.png) - The character will examine the item under the cursor.

![](ico_5.png) - The character will use the item under the cursor.

![](ico_6.png) - This is used when no other icon is aplicable.

If you click on an item the character will examine it. If the item can be picked up, you can click on the item again to do so. If it cannot be picked up, the character will simply describe it again.

You can view the items in your inventory by right clicking. You can hide the inventory by right clicking again. When you click on an item in the inventory the character will examine it. You can also drag and drop items from inventory on other items or on objects on the scene. If it is possible to use these items together, the character will do so.

When either changing locations or entering buildings, you can double click instead of clicking just once. This will change the location immediately without requiring the character to walk to the door or to the edge of the screen. This will also skip all transition animations.

Pressing escape in game will show the ingame menu. It works just like the main menu with following changes:

* New Game is replaced by Save Game, which allows you to save the game.

* New button added Back to Game, which closes the menu.

* Quit replaced by Quit to menu, which navigates back to the main menu. Warning: all unsaved progress will be lost when entering the main menu.

## Walkthrough

If you ever get stuck trying to finish the game, this chapter can help you. However, we recommend you first explore the game on your own, mainly because this chapter lists just the shortest sequence of actions you can take to finish the game, but you will be missing on some amusing dialog in the game by just doing the strictly necessary actions.

So, without further ado, here is the walkthrough:

1. You need to create an account in the bank. Go to the city in the present, enter the bank (the building in the center) and talk with the banker.

2. Leave the bank. Use the pedestal with the bird skeleton to travel to the future.

3. Go to the bank in the future and use the machine dispensing cleaning robot.

4. Pick up the the cleaning robot.

5. Go back to the present, to the area right next to the river, the one with the grave. Use the pedestal with the egg to travel to the past.

6. Go to the village and enter the house on the left. You will see a potter here. Use the cleaning robot on him to "clean" him.

7. With the potter gone, you can pick up the vase.

8. Go back to the area with the grave.

9. Pick up both parts of the shovel and combine them to create a whole shovel.

10. Use the vase on the grave to put it in.

11. Use the shovel on the grave to bury the vase.

12. Use the pedestal with the bird to travel to the present.

13. Use the shovel on the grave to dig up the grave.

14. Pick up the vase.

15. Go to the city and enter the house on the left, the antique shop.

16. Sell the vase, either by talking to the seller or by using the vase on her.

17. Pick up the money.

18. Go outside and to the bank.

19. Deposit the money by either talking to the banker or by using the coins on him.

20. Go to the future bank.

21. Withdraw money by speaking to the banker.

22. Pick up the money.

23. Go outside.

24. Use the money on the vending machine.

25. Pick up the chip.

26. Go to the village in the past and enter the house on the right.

27. Talk with the mayor to convince him to build a bridge over the chasm.

28. Go back to where you started and cross the river.

29. Watch the credits to end.

30. Celebrate your amazing victory.

# Technical Guide

So, you finished the game and now you want to understand how it works under the hood. Before proceeding, please make sure that you have the Unreal Engine 4.19.2 installed. For further information on installing the engine, see the Adventure Plugin Installation Guide. 

## Getting Started

First you need to open the project. First, open the file

{PluginPackageDir}\Demo\Source\TimeLapsusDemo.uproject, where PluginPackageDir is the folder where you extracted the plugin package. Opening it for the first time might take a while, so please be patient.

With the project loaded, you can click on the Play button in the toolbar near the top of the screen and you can play the game just like you would play the regular game. Note that when playing in editor the localization does not work.

When paused or not playing, you can click on the individual actors on the scene or on actors in the world outlier (in the top right corner). When you do so, the properties pane will appear where you can see and modify the properties of the actor. On some actors you will see a blue "Edit Blueprint" button which opens the blueprint with the actor’s behavior. So if there is some particular element you are curious about, this is how you can quickly figure it out.

There are also level blueprints that are specific to individual levels. You can access by clicking on "Blueprints->Open Level Blueprint" in the toolbar.

This is how you can access the behavior of all objects in the game. You can also open the blueprints by navigating to them in the content browser and opening them.

Now we will explain the content structure of the game. We will not explain the basics - details of how blueprints work etc. We assume some basic familiarity with Unreal Engine. We will also only briefly explain Adventure Plugin related concepts, as those are thoroughly described in a separate document, Adventure Plugin Designer Documentation.

## Demo Content Assets

### Quests

In this folder you can see the quests describing the game. Quest describes the actions the player must take in order to complete the game. It also describes the order in which the player must take the actions. A quest can also store variables tracking anything else you might want. In our game you can see 4 quests:

* MainQuest: This quest describes the entire game from start to finish, every action the player must take.

* AncientifyVaseQuest: This quest describes the process of making the vase ancient - burying the vase in the past and digging it out in the future.

* GetCreditsQuest: This quest describes the process of making a lot of money by depositing money in the bank and withdrawing them in the future.

* ItemsData: This quest is a dummy quest that actually does not contain any action and is completed by default. However, we store variables in this quest, specifically which items were and which were not examined. We added it to demonstrate that quests do not have to be actual quests, they can also serve as a variable storage.

For now, open the MainQuest asset. An editor window for quest graphs will appear. Here you will see that the sequence of actions for completing the game is actually quite linear. And that does represent the game - there is always only one action the player can take to progress. The graph could be much more complex, however, that was outside of scope for this demo.

If you have no nodes selected, you will see additional variables in the property pane on the right. For example, TeleportUsed tracks whether the user has already used the teleport. That is needed because the first time the teleport is used, a dialog should be launched, with the character being surprised about being where he is.

And you will also see Quest Events. These serve to communicate between different parts of the game. For example, when dispensing the Cleaner Bot, first a dialog is played, after which the dispensing animation will be showed. So the dialog does not only show the dialog, it also fires the CleanerDispensing event, notifying everyone that the Cleaner Bot should now be dispensed. Meanwhile, on the scene, the level blueprint is already waiting for that event. And once it is fired, it will start the dispensing animation.

And that is everything. Quests are really just data stores and event handlers, they themselves do not contain any logic, they just define what should be done.

### Characters

In the Characters folder you will see an Adventure Character blueprint asset for every character that can speak in the game. Each of these assets has some basic properties like Name, Icon etc. You can also define combinations on the character, for example there is a combination in the Banker Character. Combinations are defined in the Event Init Combinations blueprint event. But that is quite complex, so both the combinations and individual properties will be described in the Designer Documentation in more detail.

### Items

In this Items folder you will see an Inventory Item blueprint asset for every item you can pick up in the game. Like Characters, you can also define combinations and some basic properties. You can also define behaviors, e.g. what will happen when the user examines this item.

### Dialogs

In the dialogs folder you will find all of the dialogs in the game. In each asset there are all dialogs regarding some specific character or object. They are:

* AutomatDialog: Has dialogs about the Babel chip vending machine.

* BankerDialog: Has dialogs with the banker in the present.

* GraveDialog: Has dialogs about the graves in both the present and the past.

* ItemExamination: Has dialogs for examining items.

* LaraDialog: Has dialogs with the antique seller.

* MayorDialog: Has dialogs with the mayor in the past.

* Monologs: Has monologs of the main character, not involving anyone else.

* PotterDialog: Has dialogs with the potter.

* Robobanker: Has dialogs with the banker in the future.

* TeleportsDialog: Has dialogs about the teleports to the past, future and present.

For now, open the BankerDialog. You will see window similar to the quest graph editor. On the right side, in the property pane you will be able to select which characters are speaking in this dialog.

In the graph itself you can see the flow of the actual dialog with the banker. There are three places where the dialog can start:

* MAIN ENTRY POINT: Default place to start the dialog when the player talks to the banker.

* ENTRY POINT: On Use Coins: The dialog will start here when the player uses coins on the banker, i.e. deposits the money.

* ENTRY POINT: On Use Other: The dialog will start here when the player attempts to use something else on the banker, like using shovel on him.

When the dialog starts, it starts in some node. The dialog will then follow the arrows, doing what the nodes represent along the way and eventually it will end somewhere without an arrow, ending the dialog.

The green nodes are lines said by the player, the red ones are said by the NPC, in this case the banker.

The nodes that start with IF have some condition. They also have True and False output pins. If the condition is true, the arrow from the True pin is followed. Otherwise the arrow from the False pin is followed. In this graph, the "If Coins IN INVENTORY" node checks whether the player has the coins in inventory. If he does, he can deposit them.

The yellow node, OPTIONS, gives the player the chance to select the next player line from a list of responses. When options node is reached, we start checking the outgoing arrows. If it finds a green node, i.e. player line, that node is presented to the player as a dialog option. If something else is found, the arrow from that node is followed and we try again. And so on and so forth until the end of dialog or a player line is reached. In this dialog, the "Well in the end I did manage to scrape together a small fortune" is only presented to the player if she has coins in the inventory. On the other branch (Howdy/Leave/Leave), a player line will always be found, so one option will always be presented. Note that in this game, the game auto-selects the option if only one should be presented to the player. The FB output pin on the options node is followed if no options would be presented to the player.

It should be obvious what the other nodes do from their names. They can do a lot - modify inventory, modify game variables, fire events… All of which will be described in the Designer Documentation in more detail.

### Blueprints

In this folder you can find non-item non-character blueprints that define behavior of all actors and widgets in the game. Some specific ones will be described later in more detail, here is just a high level overview. It has these subfolders:

* Area: Contains blueprints that specify areas the user can click on, but which are not visible in the game.

* Combinations: Contains a custom combination, to demonstrate that it is possible to create custom combinations representing anything.

* Components: Components are blueprints that can be added to other actors and give them some behavior. For example a component that can handle clicking on an actor or another that can specify the cursor to be displayed when the mouse is over the actor.

* InteractiveObjects: Generic objects the user can interact with - an item that can be picked up, an NPC that can be talked to and a teleport for going to the past. It also contains a base class specifying behavior these classes have in common.

* Interfaces: Interfaces can be added on blueprints do show to other actors that they support some behavior. In this folder you can find the ISpawnPoint Interface that is used to find spawn point by name. There is also the IUseTarget interface. This specifies that the user can combine the actor with some inventory item.

* Levels: Contains blueprints specific to individual levels, e.g a blueprint representing the bridge across the river, defining both how it looks and when should it spawn.

* Player: Defines blueprints specific to the player character.

* Save: Contains the custom save game object used for this game. Saving and loading is just about serializing and deserializing some object that has the state of the game. The Adventure Plugin specifies a save game object that contains all quest variables, inventory etc. Time Lapsus Demo extends it with data specific to this game, i.e. the player position and the level in which he is right now.

* UI: Contains user interface elements

* Utils: Contains miscellaneous blueprints that do not fit in other categories.

The blueprints which we think are either complex or important will be described in a separate chapter.

### Other Assets

The other assets are standard Unreal Engine assets and do not require more explanation than just stating that they exist.

* Fonts: Contains the font used in the game.

* Levels: Contains all of the levels in the game.

* Localization: Contains localization data. Auto filled by Unreal Engine 4.

* Materials: Contains the materials used in our game.

* Sequences: Contains animation sequences, like the fight with the potter.

* Sounds: Contains all sound and music in the game.

* Sprites: Contains game sprites and flipbooks. They are based on textures in the Textures folder.

* Textures: Contains all textures used in the game.

 

## Important Blueprints

In this chapter we will introduce the blueprints that we think should be described more, whether because they are critical to the Adventure Plugin or because they are used often.

### Dialog/Inventory Presenter

The Adventure plugin itself handles only the game logic and data - what quests are complete, what are the values of game variables, the flow of dialogs etc. But it cannot show anything, at least not directly. To show something, the designer must create so called Presenter classes and let the Adventure Plugin know that it should use them.

If you click on Edit->Project Settings->Adventure Plugin in the menu, you will see a lot of classes you can use to customize the plugin. But most of these work fine by default and there is no reason to change them. However, there are two Default Presenter entries, one in the Dialog section, one in the Inventory section. These are the classes used for showing dialogs and inventory to the player. And you will see these do have custom classes set, DialogWidgetBP and InventoryWidgetBP. 

Both of these are straightforward implementations of the interface specified in the Designer Documentation, so they will be not be described here in more detail. Just know that these are the presenters and that these classes can show or hide the inventory, dialogs and inventory options.

### Adventure Game Mode

We used game mode to add behavior that should be the same across all levels, especially:

* It parses the url used to open the level and spawns the player at the correct position

* The game mode manages the label widget at the top of the screen that shows the name of the action to be executed right now. 

* It handles the fade transition animation.

### Main Player Controller

This is the class that handles the player input. It can:

* Make the player character move to some specific position. Other blueprints can call the Move to method. The controller will then raise the Movement Stopped method once the character finishes walking to that position.

* Handles cursor/label change. There are three cases how the cursor can be handled:

    * The user is currently dragging an inventory item. While dragging, the normal cursor methods do not do anything. So the dragged object manually calls methods on the player controller while dragging to update the label/cursor.

    * The cursor is over an actor with a Cursor Component. In that case the Cursor Component has properties regarding the cursor label and cursor to be used.

    * Neither of these happened, use the default cursor.

* Handles clicking on the scene.

* Handles showing/hiding of the game menu.

## Game Interactable Object

This blueprint represents any object on the scene the player can click on. It is a general class meant to be subclassed. It handles the common actions:

* When clicking on the object the player should move to the object and then do some action. It can also change the player orientation.

* It supports combinations, including showing a random dialog for invalid combinations.

* It has a cursor component, which means that the Main Player Controller can change the cursor when over the object.

Concrete subclasses then specify combinations. They can override any of these methods to implement their own behavior. GameTalkableNPC, GamePickableItem and Teleport are implementations used multiple times. Items that are interactive, but are not items or characters, usually have their own class.

# Conclusion

This should be enough to get you started with the demo. There are, of course, many more things that we could describe. However, the main goal of the demo is to illustrate the capabilities of the plugin and this should be enough to get you started with that.

