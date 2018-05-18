// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AdventurePluginEditorMode : ModuleRules
{
    public AdventurePluginEditorMode(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "AdventurePluginEditorMode/Public"
				// ... add public include paths required here ...
			}
            );

        PrivateIncludePaths.AddRange(
            new string[] {
                "AdventurePluginEditorMode/Private",
				// ... add other private include paths required here ...
			}
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "AdventurePluginEditor"
				// ... add other public dependencies that you statically link with here ...
			}
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "UnrealEd",
                "LevelEditor",
                 // ... add private dependencies that you statically link with here ...
                "Core",
                "AssetTools",
                "UnrealEd", // for FAssetEditorManager
                "KismetWidgets",
                "KismetCompiler",
                "BlueprintGraph",
                "GraphEditor",
                "Kismet",  // for FWorkflowCentricApplication
                "PropertyEditor",
                "EditorStyle",
                "Slate",
                "SlateCore",
                "Sequencer",
                "DetailCustomizations",
                "Settings",
                "RenderCore",
            }
            );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}