// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
    public class AdventurePluginEditor : ModuleRules
    {
        public AdventurePluginEditor(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
                new string[] {
                    "AdventurePluginEditor/Public"
					// ... add public include paths required here ...
				}
                );

            PrivateIncludePaths.AddRange(
                new string[] {
                     "AdventurePluginEditor/Private"
					//"Developer/AdventurePluginEditor/Private",
					// ... add other private include paths required here ...
				}
                );

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
					// ... add other public dependencies that you statically link with here ...
				}
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
					// ... add private dependencies that you statically link with here ...
                    "MessageLog",
                    "Projects",
                    "InputCore",
                    "UnrealEd",
                    "LevelEditor",
                    "CoreUObject",
                    "Engine",
                    "Slate",
                    "SlateCore",
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
}