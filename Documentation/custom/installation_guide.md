# Installation Guide {#installation}

# Introduction

This is the installation guide for the Adventure Plugin. This plugin was developed on Windows 10 64-bit operating system, was not tested on any other systems and is not guaranteed to work anywhere else.

Also, when we refer to the main Adventure Plugin package, we mean the root folder of this documentation, i.e. the parent folder of the folder where this file is located.

# Requirements

Though the engine is multiplatform, our plugin was developed and tested only on PCs. The PC must run Windows 10 64-bit and must be able to run Unreal Engine 4.19.2 Which means that, based on the official Unreal Engine’s requirements, the machine should have:

* 8GB RAM

* Quad-core Intel or AMD processor

* DX11 compatible video card.

Unreal Engine 4.19.2 might run on worse laptops and desktops not meeting these requirements, but its performance would be affected.

# Installing Unreal Engine 4.19.2

First of all, you need to have the correct version of Unreal Engine installed. Without it the plugin cannot be used. You can skip the first two steps if you already have Epic Games Launcher installed and all of these steps if you have the 4.19.2 version of the plugin installed.

1. Download the Epic Games Launcher. It can be downloaded here: [https://www.epicgames.com/unrealtournament/download](https://www.epicgames.com/unrealtournament/download)

2. Launch the downloaded installer and follow the instructions.

3. Open Epic Games Launcher. 

4. On the first screen the Launcher will ask you to login. Even though the Launcher allows you to proceed without signing in, installing Unreal Engine is only possible for logged in users. So you have to login by either:

    1. If you do not have an account already, click on Sign Up and follow the instructions.

    2. Or if you do have an account, login with your credentials.

5. On the top left side of the Launcher window you can see buttons for navigation: Home, Store, Library and Unreal Engine. Select Unreal Engine.

6. On the top of the screen you should see a tab bar for navigation, with items Unreal Engine, Learn, Marketplace and Library. Select Library.

7. Near the top of the Launcher Window you should see Engine Versions text, with plus sign button right next to it. Click on the plus sign button.

8. New item should appear that would install the latest version eight now. But 4.19.2 is not the latest version. Click on the version text (4.22.0 as of the time of writing) and a combobox with all versions that can be installed will appear. Select 14.9.2.

9. Click on the install button under the version name.

10. Select the installation folder you want.

11. By clicking on Options you can select the features you wish to install. If you plan to do any programming with the plugin, we recommend you to select everything, except for the Target Platforms you do not plan to develop for. If you do not plan to do anything programming related you do not have to install anything except for the Core Components, which cannot be deselected. Once you select everything you need, click on apply.

12. Click on Install and wait for the installation to finish.

# Setting up Visual Studio

You can skip this step if you do not plan to do anything programming related. Unreal Engine 4.19.2 requires Visual Studio 2017 to be installed, with C++ compiler support. Also it needs Windows 8.1 SDK and Windows 10 SDK. Here you can see Visual Studio 2017 installation instructions for Unreal Engine, as well as some tips for setting up the environment to make developing for Unreal Engine easier: [https://docs.unrealengine.com/en-us/Programming/Development/VisualStudioSetup](https://docs.unrealengine.com/en-us/Programming/Development/VisualStudioSetup)

# Using the plugin

Once you have everything else setup, you can install and use the plugin itself. There are two main ways you can use the plugin: By using a template or by setting up everything manually. Using a template is easier and is the recommended way of getting familiar with the plugin. 

There is also a third section called "Using plugin from source", which is relevant if you plan to modify the plugin.

## Creating project from template

This is the recommended way of using the plugin. The template contains a simple 2D point and click adventure game that demonstrates the basic plugin functionality.

1. Navigate to the Plugin\Template folder inside the main Adventure Plugin package.

2. Copy the AdventurePluginTemplate folder to {UE4InstallationFolder}/Templates folder, where {UE4Installation} is the folder where you installed Unreal Engine 4.19.2. Default installation folder is C:\Program Files\Epic Games\UE_4.19.

3. Open Epic Games Launcher and navigate to UnrealEngine in the left bar. Then in the top right corner press Launch Unreal Engine 4.19.2. If you have multiple versions installed, you might have to press the arrow next to the Launch button to select the correct version.

4. Unreal Project Browser should now appear. Select the New Project tab.

    1. If instead of Project browser an existing project is opened, you have to create a new project. You do that by selecting File->New Project in the top menu.

5. Select the Adventure Plugin template. It should be in the Blueprint tab.

6. Under the list of templates you should see three boxes with additional project settings. Make sure the first one says Desktop/Console, second one says Maximum Quality and the third one says No Starter Content, as these are the only settings which were tested.

7. Optionally change the folder and name of the project in the bottom part of the screen.

8. Click Create Project.

You should now see a simple demo project which demonstrates the capabilities of the plugin. You can hit the play button in the top toolbar to see it in action. 

## Using the plugin without a template

While using the template is the best way to get used to the plugin, when making a game you might instead choose to use just the plugin without all the other blueprints and content included in the template. For example, the template is not really useful when making 3D games. Here are the setup instructions for using the plugin:

1. Navigate to the folder Plugin/Packaged inside the main Adventure Plugin package.

2. Now decide if you want to use your plugin as an editor plugin or as a project plugin.

    1. Editor plugins are usable across all projects. To add the plugin as an editor project, copy the AdventurePlugin folder to {UE4InstallationFolder}\Engine\Plugins folder, where {UE4Installation} is the folder where you installed Unreal Engine 4.19.2. Default installation folder is C:\Program Files\Epic Games\UE_4.19.

    2. Project plugins are available only for a specific project. To add the plugin as a project plugin, copy the AdventurePlugin folder to {ProjectRoot}/Plugins directory, where {ProjectRoot} is your existing project folder, the folder with the .uproject file. This will install the plugin for that project only.

3. Open the project where you want to use the plugin and click on Edit->Plugins in the top menu.

4. List of installed plugins should appear. Find AdventurePlugin in the list and click on it.

5. Make sure that Enabled is checked. This enables the plugin for your project, including all custom Data Assets, classes and blueprint methods.

6. There is a bug in Unreal Engine 4.19.2 that makes it impossible to create shipping builds using our plugin. To fix it:

    3. Click on Edit->Project Settings in the top menu.

    4. On the left side is a list of settings categories. Find Editor->Blueprints and click on it.

    5. In the Blueprints configuration, make sure that "Use Compilation Manager" is unselected.

7. Plugin itself cannot do anything visible to the user directly, it just handles the logic. To actually show dialogs and inventory to the user, you must register presenter classes. You need to create your own classes implementing DialogPresenterInterface and InventoryPresenterInterface. They are described in more detail in the User Documentation.

8. Go to Edit->Project Settings in the top menu. In the Project Settings window that appears, go to Plugins->Adventure Plugin section. 

9. In both Inventory and DIalog sections there is a combobox for selecting a Default Presenter. Select your custom presenters in both of these boxes.

Now the plugin is ready, the Quest and Dialog data assets are registered and all of our methods are working properly. For more information on actually using the plugin, see the User Documentation.

## Using the plugin from source

To use the plugin from source, you must have Visual Studio 2017 already installed. See the section "Setting up Visual studio" above. To use the unpackaged version of plugin from source codes, do the following:

1. Navigate to the folder Plugin/Source inside the main Adventure Plugin package.

2. Right click on the AdventurePluginDev.uproject file and click on Generate Visual Studio Project Files. If you cannot see this option, you have probably not installed Unreal Engine or Visual Studio 2017 correctly.

3. If you have multiple versions of Unreal Engine installed, you will now be asked to select the version for which you want to generate files. Select 4.19.2.

4. Open the .sln file.

5. As a target, select either "DebugGame editor" or “Development editor”.

6. Run or Debug the project.

This should open a project we have used for development. 

