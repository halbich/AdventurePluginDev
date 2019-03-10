# Installation Guide {#installation}

# Introduction

This is the installation guide for the Adventure Plugin. This plugin was developed on Windows 10 64-bit operating system, was not tested on any other systems and is not guaranteed to work anywhere else.

Also, when we refer to the main Adventure Plugin package, we mean the root folder of this documentation, i.e. the parent folder of the folder where this file is located.

Be warned that this might take a lot of disk space:

* Unreal Engine 4 itself can require up to  40 GB of space.

* Visual Studio can also require up to 40 GB of space, depending on the selected features.

* The demo project, once compiled, can take up to 20 GB of space.

* The project from building from source, AdventurePluginDev, requires cca 10GB of space.

# Requirements

Though the engine is multiplatform, our plugin was developed and tested only on PCs. The PC must run Windows 10 64-bit and must be able to run Unreal Engine 4.19.2 Which means that, based on the official Unreal Engine’s requirements, the machine should have:

* 8GB RAM

* Quad-core Intel or AMD processor

* DX11 compatible video card.

Unreal Engine 4.19.2 might run on worse laptops and desktops not meeting these requirements, but its performance would be affected.

# Installing Unreal Engine 4.19.2

First of all, you need to have the correct version of Unreal Engine installed. Without it the plugin cannot be used. You can skip the first two steps if you already have Epic Games Launcher installed and all of these steps if you have the 4.19.2 version of the Unreal Engine installed.

1. Download the Epic Games Launcher. It can be downloaded here: [https://www.epicgames.com/unrealtournament/download](https://www.epicgames.com/unrealtournament/download)

2. Launch the downloaded installer and follow the instructions.

3. Open Epic Games Launcher. 

4. On the first screen the Launcher will ask you to login. Even though the Launcher allows you to proceed without signing in, installing Unreal Engine is only possible for logged in users. So you have to login by either:

    * If you do not have an account already, click on Sign Up and follow the instructions.

    * Or if you do have an account, login with your credentials.

5. On the top left side of the Launcher window you can see buttons for navigation: Home, Store, Library and Unreal Engine. Select Unreal Engine.

6. On the top of the screen you should see a tab bar for navigation, with items Unreal Engine, Learn, Marketplace and Library. Select Library.

7. Near the top of the Launcher Window you should see Engine Versions text, with plus sign button right next to it. Click on the plus sign button.

8. New item should appear that would install the latest version right now. But 4.19.2 is not the latest version. Click on the version text (4.22.0 as of the time of writing) and a combobox with all versions that can be installed will appear. Select 4.19.2.

9. Click on the install button under the version name.

10. Select the installation folder you want. Do note that this might take up to 40 GB of space, depending on the selected features.

11. By clicking on Options you can select the features you wish to install. If you plan to do any programming with the plugin, we recommend to select everything, except for the Target Platforms you do not plan to develop for. If you do not plan to do anything programming related you do not have to install anything except for the Core Components, which cannot be deselected. Once you select everything you need, click on apply.

12. Click on Install and wait for the installation to finish.

    * In case of an error during installation, please first remove the version being installed from the library and then go to the installation folder and manually delete all remaining files. Then, retry the installation.

# Setting up Visual Studio

You can skip this step if you do not plan to do anything programming related. Unreal Engine 4.19.2 requires Visual Studio 2017 to be installed, with C++ compiler support. Also it needs Windows 8.1 SDK and Windows 10 SDK. Here you can see Visual Studio 2017 installation instructions for Unreal Engine, as well as some tips for setting up the environment to make developing for Unreal Engine easier: [https://docs.unrealengine.com/en-us/Programming/Development/VisualStudioSetup](https://docs.unrealengine.com/en-us/Programming/Development/VisualStudioSetup)

# Demo project

We created a small game that showcases everything our plugin is capable of. You only need to have the Unreal Engine installed to try it out. See the Time Lapsus Demo Documentation for details. That document is the best way to get familiar with our plugin. 

# Using the plugin in custom projects

Once you have everything else set up, you can install and use the plugin itself. There are two main ways you can use the plugin: By using a template or by setting up everything manually. Using a template is recommended if creating a 2D adventure game, as it contains some blueprints that can speed up development.

There is also a third section called "Using plugin from source", which is relevant if you plan to modify the plugin.

## Creating project from template

This is the recommended way of using the plugin. The template contains two 2D adventure game levels that demonstrate the basic plugin functionality.

1. Navigate to the Plugin\Template folder inside the main Adventure Plugin package.

    - Copy the AdventurePluginTemplate folder to {UE4Installation}/Templates folder, where {UE4Installation} is the folder where you installed Unreal Engine 4.19.2. Default installation folder is C:\Program Files\Epic Games\UE_4.19.

2. Open Epic Games Launcher and navigate to UnrealEngine in the left bar. Then in the top right corner press Launch Unreal Engine 4.19.2. During the first launch, UE4 will request a firewall exception. Grant it. If you have multiple versions installed, you might have to press the arrow next to the Launch button to select the correct version.

3. Unreal Project Browser should now appear. Select the New Project tab.

    - If instead of Project browser an existing project is opened (i.e., UE4 editor auto-starts up and load the existing project you have been previously editing), you have to create a new project. You do that by selecting File->New Project in the top menu.

4. Select the Adventure Plugin template. It should be in the Blueprint tab.

5. Under the list of templates you should see three boxes with additional project settings. Make sure the first one says Desktop/Console, second one says Maximum Quality and the third one says No Starter Content, as these are the only settings which were tested.

6. Optionally change the folder and name of the project in the bottom part of the screen.

7. Click Create Project.

8. Note that loading of a project might make some time, up to 5 minutes in extreme cases. And the window might appear stuck, with percentages not increasing. Do not worry, this is normal, just wait for a while

You should now see a simple project which demonstrates the capabilities of the plugin. You can hit the play button in the top toolbar to see it in action. The template uses the same structure as the Time Lapsus demo. So if you want to learn more about the template - how to use it, what are some notable blueprints etc., please first get familiar with the demo by reading the Time Lapsus Demo Documentation document. The template is just the demo project with much less content.

## Using the plugin without a template

The template is the quick way to get started when creating 2D adventure games. However you might instead choose to use just the plugin without all the other blueprints and content included in the template. For example, the template is not really useful when making 3D games. Here are the setup instructions for using the plugin:

1. Navigate to the folder Plugin/Packaged inside the main Adventure Plugin package.

2. Close any running instances of Unreal Engine 4 before installing the plugin.

3. Now decide if you want to use your plugin as an editor plugin or as a project plugin.

    * Editor plugins are usable across all projects. To add the plugin as an editor project, copy the AdventurePlugin folder to {UE4Installation}\Engine\Plugins folder, where {UE4Installation} is the folder where you installed Unreal Engine 4.19.2. 

    * Project plugins are available only for a specific project. To add the plugin as a project plugin, copy the AdventurePlugin folder to {ProjectRoot}/Plugins directory, where {ProjectRoot} is your existing project folder, the folder with the .uproject file. This will install the plugin for that project only.

4. Open the project where you want to use the plugin and click on Edit->Plugins in the top menu. You can create any type of project you want, the plugin is not dependent on anything.

5. List of installed plugins should appear. Find AdventurePlugin in the list and click on it.

6. Make sure that Enabled is checked. This enables the plugin for your project, including all custom Data Assets, classes and blueprint methods. 

    * This action will require editor restart, so restart Unreal Engine after enabling the plugin.

7. There is a bug in Unreal Engine 4.19.2 that makes it impossible to create shipping builds using our plugin. To fix it:

    * Click on Edit->Project Settings in the top menu.

    * There is a list of settings categories on the left side. Find Editor->Blueprints and click on it.

    * In the Blueprints configuration, make sure that "Use Compilation Manager" is unselected.

8. Plugin itself cannot do anything visible to the user directly, it just handles the logic. To actually show dialogs and inventory to the user, you must register presenter classes. You need to create your own classes implementing DialogPresenterInterface and InventoryPresenterInterface. They are described in more detail in the Developer Documentation.

9. Go to Edit->Project Settings in the top menu. In the Project Settings window that appears, go to Plugins->Adventure Plugin section. 

10. In both Inventory and Dialog sections there is a combobox for selecting both the Dialog and Inventory Presenter. The fields are called Default Presenter, one is in the Dialog Section, one is in the Inventory. You must set the custom presenters you created in step 7 in these fields, otherwise the dialogs and inventory will not do anything.

Now the plugin is ready, the Quest and Dialog data assets are registered and all plugin methods are working properly. For more information on actually using the plugin, see the Developer Documentation.

## Using the plugin from source

To use the plugin from source, you must have Visual Studio 2017 already installed. See the section "Setting up Visual studio" above. To use the unpackaged version of plugin from source codes, do the following:

1. Navigate to the folder Plugin/Source inside the main Adventure Plugin package.

2. Right click on the AdventurePluginDev.uproject file and click on Generate Visual Studio Project Files. If you cannot see this option, you have probably not installed Unreal Engine or Visual Studio 2017 correctly.

    * If you have multiple versions of Unreal Engine 4 installed, you should ensure that the project uses the correct version before clicking on Generate Visual Studio Files. Click first on Switch Unreal Engine version when you right click on the project and select 4.19.2.

3. You might be asked to select the version for which you want to generate files. Select 4.19.2.

4. Open the .sln file.

5. As a target, select either "DebugGame editor" or “Development editor”.

6. Run or Debug the project.

This should open a project that we use for plugin development. You can pick up two parts of the shovel here, combine them and then talk to the teleport to test the dialog system. This does not have any concrete functionality, there is no goal here, this project was just used for testing individual components of the Adventure Plugin.

### Troubleshooting

If the project fails to compile, there is probably something wrong with the way the development environment is set up. Unreal Engine 4 is a complex tool we have no control over, so it is difficult for us to foresee what problems you might encounter. However are a few tips that might help you solve the most common problem - missing SDKs:

* Make sure that you have the Windows SDK 8.1 and Windows SDK 10 installed. 

* Try reinstalling both SDKs.

* Try uninstalling both SDKs, restarting the computer, installing the SDKs again.

Other than that you can try reinstalling the Unreal Engine and Visual Studio. If that fails you can try searching for help online or contacting our team for support. The compiler output should have details regarding the problem.

# Next Steps

Once you have the project running, you can read other parts of the documentation:

* Time Lapsus Demo Documentation introduces the demo project - how to play it and how it works.

* Adventure Plugin Designer Documentation introduces everything related to the plugin that can be useful to designers, i.e. everything that can be done from blueprints.

* Adventure Plugin Designer Documentation explains how the plugin works under the hood. It provides high level overview of our C++ classes and it also describes ways in which you can extend the plugin.

* Adventure Plugin Development Documentation documents the process of creating the plugin - who worked on it, how they worked on it and why. It also contains some retrospective about the decisions we made.

