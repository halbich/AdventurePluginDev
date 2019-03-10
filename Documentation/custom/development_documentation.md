# Development Documentation {#development}

# Introduction

In this document we want to briefly discuss the development of this project. In the first chapter, which you are reading right now, we will introduce the project - what does it do, why did we choose to do it and how it compares with the competition. Next we will document the development process itself, divide the development into stages and document what did various members of the team do during those stages. In the chapter after that we will look back on the various decisions we made when making this plugin and discuss them. In the last chapter we will mention more features that could be added to the plugin.

## Requirements

The user should be familiar with our plugin, so she should have read the Designer Documentation and the Programming Documentation.

## What is the Project About

We created a plugin that makes it easier to create adventure games in Unreal Engine 4. Unreal Engine 4 is an existing game engine which greatly simplifies game development. 

In adventure games the player controls a character, moves in a game world, talks to characters, picks up items, uses them on other items, on characters and a lot more, all in order to solve some puzzles created by game designers.

Our plugin is not a full featured toolset in which you could create an entire adventure game without doing anything in code. That would be well beyond the scope of this project. Instead, we identified three main issues which have to be solved in all adventure games and made a plugin that addresses them:

* Creating dialogs. In most adventure games, player can talk to other characters and can select what will her character say. A dialog can also often have branches depending on the state of the game. We created a graph editor for designing these dialogs.

* Designing the flow of the game. Adventure games tend to boil down to a number of steps the player must do with dependencies between them, e.g. the player must first find a key and then open a locked chest. Our plugin allows creation of these dependency graphs directly in the editor in a way with which game scripts can interact. This makes designing of the graphs easier and it also makes subsequent implementation of the design in game scripts easier.

* In most adventure games, players can pick up a lot of items, which have their own behaviors and properties. Our plugin simplifies the process of designing these items by creating a blueprint that all of these items can inherit from. It also provides methods for managing the player’s inventory at runtime.

## Why Did We Create the Plugin

In the winter semester of 2015, Pavel Halbich and Matouš Kozma were members of a team which created a small adventure game as part of the Computer Games Development course. The game was made in the Unity Engine and was well received. As the members of the team got along well together, they decided they want to make a larger version of the game that could be distributed commercially. 

They thought about technologies that could be used for that and in the end decided against the Unity Engine and decided to use Unreal Engine 4 instead. Even though Unity is easier to learn than Unreal Engine 4 and would probably be easier for our designers to use, we eventually decided to use Unreal Engine 4 for the following reasons:

* Unreal Engine 4 source code is available to programmers. This is by far the greatest advantage of Unreal Engine 4. Whenever we want to extend the plugin, we can see how a similar feature was implemented in the engine. Whenever there is a problem with the plugin, we can step through the engine code and find the problem.

* Unreal Engine 4 has blueprints. While there are plugins for Unity which also give it a support for a visual scripting language, Unreal Engine 4 Blueprints are an integral part of the engine and are much better integrated. And while blueprints might not be that important for programmers, they are invaluable to designers. They are also great for rapid prototyping.

* We already made a game in Unity and we wanted to learn how to work with a new engine.

* Unity plugin for creating Adventure Games already exists (more on that later).

* Pavel Halbich also had a personal preference for Unreal Engine 4.

Once we chose the engine, we wanted to find a way to treat the development process of the game as a Software Project. After all, if we have to spend 9 months working on a large piece of software, it might as well be a personal project we really want to work on. And we realized that making a simple adventure game would probably not require multiple people working on the game for 9 months. There the idea of a plugin first emerged, that we should make an adventure game toolset. It is not only a great software project, it is also closer to how real game development works than the approach used in our first project, for which we just created ad hoc scripts for everything manually. Also, we think making an Unreal Engine 4 plugin is probably a rare experience among aspiring game programmers, as most of them will not bother with creating engine tools and if they do, they will probably choose the Unity engine.

At first it was supposed to be a full featured plugin that could do everything, but we quickly realized that that goal is well beyond the scope of a software project. With the help of our supervisor we managed to identify the key areas our plugin could address and which we could do in 9 months.

We also did some research on existing solutions for making adventure games. For Unity we found an excellent plugin called Adventure Creator. This tool can be used to make an entire adventure game without ever touching code. However, this only reinforced our choice to make the plugin in Unreal Engine. After all, why create a plugin that does exactly the same thing as an already existing, mature solution.

But we found no similar solutions for Unreal Engine 4. Here are similar plugins we could find, but which differ from our plugin in some key areas.

* First Person Story Adventure Template: This template is focused only on 1st person 3D adventure games and has no support for dialogs. Looking through the features, it does not support any of the systems supported by our plugin.

    * [https://www.unrealengine.com/marketplace/first-person-story-adventure-template](https://www.unrealengine.com/marketplace/first-person-story-adventure-template)

* Not Yet Dialogue System: To us it seems that this dialog system offers a lot less features than we do and is really meant just to create very simple dialogs.

    * [https://www.unrealengine.com/marketplace/en-US/not-yet-dialogue-system](https://www.unrealengine.com/marketplace/en-US/not-yet-dialogue-system)

* Dialogue Tree and Quest System: This plugin is a lot closer to what we are doing. Unfortunately we cannot properly analyze it without buying it, which we are not willing to do. Still, looking at it it seems like it is unnecessarily complex for adventure games. Basically, this looks like a plugin that can do anything but with a steep learning curve. Also, it did not exist in this advanced form back when we were starting the project.

    * [https://www.unrealengine.com/marketplace/dialogue-tree-and-quest-system](https://www.unrealengine.com/marketplace/dialogue-tree-and-quest-system)

* Ultimate Dialogue: This plugin is focused only on dialogs and seems to be quite tightly bound to 3D characters. And their dialog editor seems to hide conditions, which might make it nicer to read, but it also makes it harder to follow the actual flow of the graph. It also did not exist back when we were starting the project.

    * [https://www.unrealengine.com/marketplace/en-US/ultimate-dialogue](https://www.unrealengine.com/marketplace/en-US/ultimate-dialogue)

And as we found no existing solutions for adventure games specifically, we decided to create our own plugin, which we would then later use to create the game.

## Who Created the Plugin

* Pavel Halbich: Programming.

* Matouš Kozma: Project management and programmer.

* Marek Polák: Programming

The project was also supposed to contain a demo level created by our designer Petr Janda and our artist Pavel Liška. Unfortunately they could not complete the demo level on time, even though development of the game is progressing. So the demo is a modified version of the original Time Lapsus, a game we made 3 years ago.

# Project timeline

Now we will go through history, all the way back to the original Time Lapsus game made in 2015. We will describe the different stages this project took, marking the important dates in regards to the software project.

* October 2015 - January 2016: Pavel Halbich (programmer), Petr Janda (writer/designer), Matouš Kozma (programmer) and Pavel Liška (artist) formed the TTTeam and created Time Lapsus, an adventure game about time travel, as an assignment for the Computer Games Development course. The game went on to become the best game of the semester.

* January 2016 - September 2016: Time Lapsus was well received, some polishing was done and the developers went to conferences showcasing the game. The plan to expand the game during the Software Project course was formed, but for now the plan was intentionally put on hiatus, as between school courses and jobs, none of us had any free time.

* September 2016-September 2017: We tried to find more people for the team. After a long search and some persuading, Marek Polák joined the team as a third programmer.

* October 2017-April, 2018: Though the team was formed, we still had very little free time, which is the main reason why the project was not yet officially started. We also needed to learn at least something about Unreal Engine 4 plugin development before committing to the project. In addition, our first draft for the Software Project specification was well beyond our capacities, so we were cutting features until we managed to find something that made sense and yet was creatable in 9 months.

* May 2018: A lot of time was spend trying to understand the basics of Unreal Engine 4 plugin development. It was difficult, as we were trying to learn from huge classes managing Unreal Engine 4 editors and it was quite difficult to figure out what was important and why.

* June 3, 2018: We found a 3rd party plugin called Generic Graph Editor which finally moved us forward, as we finally had a small project doing the bare minimum it had to to learn from. We finally had a clear idea of what creating a plugin entails and we were finally able to start making relevant estimations about the work needed to complete the different parts of the plugin.

* **June 13, 2018: The official start of the project.**

* June 14, 2018 - August 14, 2015:  We were analysing the project, deciding how would we implement various features. We were also identifying areas that needed further research.

    * Matouš Kozma was preparing the actual specification.

    * Pavel Halbich and Marek Polák were experimenting with the plugin, trying out things which we saw as potentially problematic, to see whether we should include them in the specification or not.

* **August 15, 2018: Successful presentation of the project specification.**

* August 2018 - October 2018: We were implementing basic components of the plugin, the graphs and the assets, as well as the basic nodes needed to test these, like Player Line, NPC Line, basing branching options. We all worked on these things together, but some people had specific responsibilities handled only by them: 

    * Marek Polák was doing most of the low level plugin work, like preparing graph editor and customizing nodes.

    * Pavel Halbich first created a small 3D demo where we could easily test things like setting variables on quests and showing simple dialogs.

    * Matouš Kozma prepared a point’n’click 2D demo with assets from the original Time Lapsus. This demo would eventually become the only demo maintained, as it was closer to what we would be eventually releasing.

* November 2018-December 2018: The basics of the plugin were done and we were working on the remaining things that were only addons to existing structures and did not drastically affect the behavior of other nodes, like combinations and save games. Again, we all worked on everything, but specifically:

    * Pavel Halbich prepared the save game system.

    * Marek Polák prepared the quest events and started implementing editor customizations.

    * Matouš Kozma prepared the combination system.

* January 2019: The plugin was mostly feature complete, but was not yet polished. We were adding minor features we missed when implementing, as well as some nice to have features.

    * Matouš Kozma prepared a simple animation system.

    * Marek Polák did a lot of stuff to make plugin more user friendly, adding a lot of customizations and custom nodes.

    * Pavel Halbich started the implementation of a debugging system for dialogs, but that was scrapped once it became clear that the intended solution would not work and that we were unlikely to finish a stable version of that feature before the project deadline.

* February 2019 - March 12, 2019: Deadline was near so we were only wrapping up. New features were added only if absolutely necessary and only if we were absolutely certain that they could not have side effects, e.g. dialog nodes. Otherwise we focused on fixing bugs and documentation.

    * Pavel Halbich was responsible for preparing the demo.

    * Matouš Kozma refactored the code to fit Unreal Engine coding style, he created most of javadoc documentation and prepared the documentation for the final project.

    * Marek Polák created javadoc documentation for editor files and fixed a lot of bugs. He also fact checked and spell checked everything Matouš Kozma wrote (which was definitely necessary) and helped Pavel Halbich with the demo.

* **March 13, 2019: Software project deadline**

# Retrospective

In this chapter we will discuss the various decisions we did or forgot to do during during the development, we will explain why did we do them and what do we think about these decisions today. We will divide this chapter into three sections: Organizational Decisions, Development Decisions and Changes From Specification. The first two sections just talk about different decisions we made, the third lists things in which we diverted from the original specification.

## Organizational Decisions

* We had meetings with our supervisor every two weeks, discussing our progress

    * Reason: Because he told us to.

    * Looking back: This was definitely a good decision, even if we were not the ones who made it. Regular meetings definitely helped us with motivation, since we did not want to go to these meetings empty handed.

* We decided to have sprint plannings every two weeks, using Trello board to organize our work and track our progress.

    * Reason: We needed to organize our progress somehow and from our experience, agile approach works best for small teams like this.

    * Looking back: This was definitely a good idea, though in practice there were setbacks. As we all had personal lives, jobs and other courses, we were not able to schedule regular meetings, so we had to schedule the meetings ad hoc. For the same reasons the amount of time we could dedicate to the project varied wildly, so in some sprints almost nothing was done and in other sprints we did great progres. Still, overall, sprint plannings worked out great, as when there was little done in one sprint, we had extra incentive to work in the next one, else we would fall behind. So if nothing else, this helped us track our overall progress.

* We failed to create a proper prioritized backlog of tasks in Trello. We had an Excel table with features we needed to implement and updated from time to time.

    * Reason: No idea. We already had the Excel sheet, creating the appropriate tasks would have been easy. But none of us did that.

    * Looking back: This was definitely a bad idea. The Excel sheet was not updated often enough and since Trello did not have all the tasks in the backlog, we had no idea how many tasks were still left. Also, there were several times when we thought we had all the features, someone checked the specification and found something we did not do yet. This would not have happened if we took the time to fill the Trello board with tasks.

* We used Slack for communication.

    * Reason: We needed a place to communicate regularly and we were all familiar with this one from our previous projects.

    * Looking back: This was a great idea. Not only does Slack help organize the conversations by channels, but since we use Slack only for projects and work related things, we can easily separate work/school life from our personal one by ignoring Slack during free time and by being available on Slack when working.

* In the last month and a half we failed to keep the Trello board up to date and we failed to have regular sprint plannings. We planned 50 days in advance what we need to do before release and who would do that, making planning decisions ad hoc using Slack, basically having a 50 day long sprint.

    * Reason: As everyone was focused mainly on their work and there was no reason to plan, this happened naturally.

    * Looking back: Not maintaining Trello Board was definitely a bad idea. Someone would write a bug in Slack, then it would get lost in a stream of messages discussing some problems and we would forget about it. However, extending the last sprint was beneficial. There was really no need to plan, priorities were set, tasks were clear, we just had to work on them and make sure we do them on time and let others know if we need help right away.

* We had a fallback plan in case our artists failed to deliver the level we wanted to present on time.

    * Reason: The artists are working on the project in free time with no outside incentives, therefore if something unexpected happens, this project is a low priority to them.

    * Looking back: Definitely a good idea. Our designer had a lot of valid personal issues preventing him from working on the game and our artist could not work on anything without the designs. So once we were sure 2 months in advance that there is no way they would be able to finish the demo on time, we started working on the demo using the assets from the original Time Lapsus

* We did not work on any documentation during the project.

    * Reason: The project kept changing and we deemed it more important to work on functionality instead of documentation.

    * Looking back: We think this was not as bad of a decision as we feared. While yes, creating all of the documentation in the last month was unpleasant, if we were working on it all the time we probably would have some obsolete information here, because we would forget to delete it or update it. But we do think that we should have been writing the javadoc in code continuously, as while yes, the methods and classes might change, when changing them you immediately see the documentation right above it, so it is easier to keep them up do date. Unlike external documents like this one which are likely to be forgotten.

* We met in person for analytical meetings, i.e. when we were making architectural decisions.

    * Reasons: Analytical meetings were only about talking and drawing things, which is better to do it person.

    * Looking back: This was definitely a good thing, the analytical meetings were very productive and we usually managed to decide on a lot of things.

* We worked from home, we met only for consultations with supervisors and for analytical meetings, rarely just for programming in the same room.

    * Reason: We were unable to schedule a day when we would all have time every week.

    * Looking back: While we definitely would have been more productive if we were meeting regularly, working from home was not the catastrophe we thought it would be.

* We cut a lot of features from the specification.

    * Reason: As there were still many unknowns, we chose to be conservative in our estimates and cut things which were not completely necessary to the project.

    * Looking back: This was definitely one of the best decisions we made. Because of this we were able to complete the project on time without being overly stressed and without rushing things. And we also had plenty of time to polish the project.

* We did not agree on coding standards when starting the project.

    * Reason: We thought we were in a prototyping phase, that lots of the classes we were developing would be thrown away and that forcing some standards and reviewing them would take a lot of time. We were also not aware of Unreal Engine 4 coding standards.

    * Looking back: This was a mistake, as when we finally decided that we should apply the Unreal Engine 4 coding standard, we had cca 200 classes to go through and review, which was a very unpleasant process.

* We used Github as source control for both the plugin and the demo projects, which were in two separate repositories.

    * Reason: We all have good experience with Github. We split the projects because we wanted the demo and plugin to be completely separate things, like it would be for people using our plugin in real life.

    * Looking back: Github for our C++ plugin was definitely great. For the demo, not so much, as working in parallel was difficult. Unreal Engine blueprints are binary files that cannot be merged. So we had to manually synchronize ourselves using Slack so we would avoid conflicts. It would have been better to use Perforce or SVN, as they support locking of files, which is a better way of handling this problem.

* We did not do code review.

    * Reason: We did not find it relevant at the time, as we had no coding standards and trusted each other to make quality code.

    * Looking back: It was not the worst decision we ever made, because we had no rules regarding coding standards and documentation. If we had, code review would have been necessary.

## Development Decisions

* We decided to prioritize simplicity and easy extensibility over maintainable and testable architecture, creating larger classes which are easier to understand and use.

    * Reason: We suspected that people extending our plugin would not bother reading the documentation and would expect to do some easy modifications directly from code.

    * Looking back: We will discuss each instance where we applied this rule separately, but overall we do think that based on the requirements we set for our projects this really was the best way to go forward.

* We chose to use a Game Context as a form of dependency injection.

    * Reason: Originally we wanted to access the plugin classes through the Game Instance, forcing the designer to use our Game Instance. However, we then found out that our classes could not access the Game Instance correctly, because they were not actors. Our solution for this problem was the creation of the Game Context class, which we started passing to all of our methods.

    * Looking back: Architecturally this was a good decision. Designers can create their game context any way they want and there is an easy default way to get one. This means that the designers can use the context in a simple way or a complex way if they require dependency injection. Although it would have been better for all classes on the Game Context to be interfaces. That would make it easier to create mock implementations for testing. However, we did not do that. Instead we forced people extending our plugin to inherit from our classes, so they always have to first see the original implementation before implementing their own. There were also technical issues - properties and event dispatchers cannot be directly exposed through interfaces, so we would need to create a lot of extra code, making the interfaces unnecessarily large. Though this could have been solved by abstract classes. But using abstract classes would prevent a single class from having multiple interfaces.
But even if architecturally speaking this was a good idea, getting a game context for every function call is a bit bothersome for the designers. But we did not find a good way to solve this issue, other than providing the Get Current Game Context method.

* We did not create any unit tests or any other automated tests.

    * Reason: We did not see them as necessary for a project of this scope and they were not required by specification.

    * Looking back: This was a good decision for a project of this scope. We never faced an issue unit tests would help us avoid - the original developers were always around and problems with existing code were usually resolved swiftly. The tests might be useful if we continue to work on the project for a longer time, if the project expands or if the developers change.

* We decided to use the Generic Graph Editor as a basis for our project.

    * Reason: It had the basic functionality for creating graphs.

    * Looking back: Great idea, finding this plugin was the thing that kickstarted the development, as we finally had a class we could use for reference that was not as complex as e.g. Behavior Tree Editor from Unreal Engine 4.

* We decided to create the demo in blueprints only.

    * Reason: We wanted to prove that it could be done.

    * Looking back: It worked, we proved we set out to do, so it was a good choice.

* We decided to localize only text, not audio.

    * Reason: While we found an easy way to localize text assets, we found no easy way to localize audio assets.

    * Looking back: We still cannot localize the audio, the only way we know of is quite complicated, so this was probably a good call.

* We decided to lock the Unreal Engine version to 4.19.2 when we started developing

    * Reason: While changes between engine versions are not that significant, there might be some changes that could break some feature of our plugin. So it is smarter to use one version only.

    * Looking back: We did not need any features from newer versions, so this was probably worth it, as we avoided potential problems with upgrading.

* We decided to make UAdventureCharacter  and UInventoryItem classes into blueprints instead of data assets.

    * Reason: Data assets do not support behaviors, which both of these classes needed to support, e.g. what will happen when using the item.

    * Looking back: It was probably a good decision, but we are not entirely sure. For data assets Unreal Engine 4 already manages their instances and provides pickers with thumbnails. And there was a way of implementing behaviors. Each data asset could have a class that implements the behavior as a property. Basically, blueprints for behaviors, data assets for data. We could also add methods on the UInventoryItem class that would just call the methods on the behavior. However, in the end we decided against this approach for following reasons:

        * It would hurt extensibility, as you cannot inherit from Data Assets properly. So it would be impossible to add new field to the item class. This issue could be solved by having some general UObject as a User Data property of the asset that could contain anything, but that brings us to the other point.

        * This approach would have been much more complicated for designers to understand. Create one object for item definition, one for its behavior, one for the actor in the scene. Explaining to them that usually, using properties and methods on the item is enough, but sometimes you might need to access properties and methods through behaviors… This approach would definitely not be friendly to the designers.

## Changes From Specification

* We decided to allow the designer to use a different game instance.

    * Reason: Once we decided to use the Game Context, there was no reason to use our game instance. We just left it as an option.

    * Looking back: There were no problems with this decision and it increased designer flexibility, so that is a good thing from our perspective.

* Whenever specification says that something is accessible through Game Instance, it is now accessible only through Game Context.

    * Reason: We started using Game Context.

    * Looking back: This caused no problems.

* Dialog Controller sends itself to the presenter, which calls the callback method on the controller. The original version expected that the presenter would expose an event dispatcher that would be fired when a long running operation would complete and the controller would bind to the event.

    * Reason: Interfaces do not support event dispatcher properties.

    * Looking back: This increased coupling slightly, as the Dialog Presenter now knows about the Dialog Controller. But other than that we do not see any issues.

* We decided to allow the user to install the plugin both as an editor plugin and as a project plugin.

    * Reason: There was no reason not to.

    * Looking back: This caused no problems.

* We removed the Generate Plugin Files menu item, as there was no reason to have it there.

    * Reason: We no longer use a custom Game Instance.

    * Looking back: This caused no problem.

* Item tags now use the Unreal Engine Gameplay Tags system, which means that the tags are not specified in the plugin configuration

    * Reason: We did not know about Gameplay Tags before and they fit our use case perfectly, so why reinvent the wheel.

    * Looking back: This caused no problems.

* We decided not to implement the Quest manager class.

    * Reason: All planned functionality was implemented on the Quest Graph in a more user friendly way.

    * Looking back: This caused no problems.

* The example implementations of presenters are not included in the plugin, they are a part of the template.

    * Reason: If not using our examples, they would clutter the project needlessly. Right now they are available only in a template if a user needs them.

    * Looking back: This caused no problems and it should make the plugin easier to use, as it does not have superfluous blueprint assets when not using a template.

# Future work

While the plugin has a lot of features, it still has a lot less features than for example Adventure Creator for Unity. In the ideal end product, the designers could create a complete 2D or 3D game in this plugin without any code and with as few blueprints as possible. That is still a long way off, so we can still work on that. There are also ways how the plugin could be made more user friendly.

So, in no particular order, here are some ways how the plugin still be improved, though the list is in no way exhaustive:

* Allow creation of custom graph nodes in blueprints.

* Add debugging features, e.g.:

    * Displaying which path did a dialog take last.

    * Breakpoints in dialogs.

    * Stepping through a dialog.

    * Showing variable values in a quest graph.

    * Adding an option for periodically taking screenshots in testing builds, so we see what did the testers actually do.

    * Log actions the tester took in some way so they can be reproduced easily.

    * Variables breakpoints that break when a variable on a quest is modified.

* Have blueprints in the template for:

    * 3D gameplay.

    * 2D gameplay using Paper2D, Creature or Spine for animations.

    * Showing 2D background moving with the player.

    * Paralaxes.

    * Levels, including streaming levels and level transition animations.

    * Having 3D characters in a 2D world.

    * Character scaling in 2D games.

    * Defining walkable areas in a user friendly way, e.g. with a brush.

    * 2D and 3D items in a scene.

    * Control schemes for controller, WASD + mouse or just mouse for both 2D and 3D.

    * Highlighting all interactive objects in the scene.

    * Hint system.

    * Prepared Save/Load blueprints.

    * Example menu.

    * Autosaving.

    * Achievements.

* Localization of audio.

* Defining multiple actions on items in a generic way, e.g. define old school Push/Pull/Eat verbs.

* Generating scripts for voice actors.

* Importing recorded audio files from exported scripts.

* Or and xor nodes for quests.

* Allow the designer to select some color scheme for the quest nodes - maybe they could have a color based on the location in which they have to be completed.

* Define a list of levels in the game. With that we could create a ChangeLevel dialog node and a picker for selecting location in quest nodes.

* Variables could have a generated UUID and could be referenced by it. This would allow the variable references on e.g. dialogs to to still work even after the original variable was renamed.

* Track references to the created variables, so that we could warn the player when deleting a variable that some asset is still using.

* Validation for dialog and quest graphs, e.g. for detecting cycles.

* Add comment boxes to dialog and quest graphs.

* Generate PropertyChanged events for flags and variables.

* Add bool variable to dialogs AllNodesAreEntryPoints. If true, this would expose all named nodes as entry points.

* Add bool variable to dialogs ForceExplicitExitNodes. If true, the validation would check if there is any way to leave the dialog except by ending in an exit node, to avoid place where the designer ends the graph by mistake by forgetting to connect pins.

* Filter dialogs by NPCs or tags.

* The dialog could have an icon based on the two speaking characters.

* Create more arithmetic flags - multiply, add, etc.

* Wait node for dialogs that would halt execution for some time.

* Play sound node for dialogs.

* Rework the animation system. 

    * Right now, only characters have the animation system implemented

    * And the animation system is very simple, it does not for example support changing of the animation in the middle of a dialog line.

    * It would be great if it were possible to link Adventure Character classes with their actors and dialogs with maps in which they appear. Then we could create a tool that could create a preview of the dialog in the actual map. This would be especially helpful in 3D.

