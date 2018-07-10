// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class AdventurePluginRuntime : ModuleRules
	{
		public AdventurePluginRuntime(ReadOnlyTargetRules Target) : base(Target)
		{
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
				new string[] {
                    "AdventurePluginRuntime/Public"
					// ... add public include paths required here ...
                }
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					//"Developer/AdventurePluginRuntime/Private",
					// ... add other private include paths required here ...
                    "AdventurePluginRuntime/Private"
                }
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core", "CoreUObject", "Engine", "InputCore",
					// ... add other public dependencies that you statically link with here ...
                    "GenericGraphRuntime",
                }
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
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
