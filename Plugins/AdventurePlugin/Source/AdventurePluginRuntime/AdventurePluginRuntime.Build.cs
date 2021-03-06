using System.IO;

namespace UnrealBuildTool.Rules
{
	public class AdventurePluginRuntime : ModuleRules
	{
		public AdventurePluginRuntime(ReadOnlyTargetRules Target) : base(Target)
		{
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
				new string[] {
                    Path.Combine(ModuleDirectory,"Public")
					// ... add public include paths required here ...
                }
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					//"Developer/AdventurePluginRuntime/Private",
					// ... add other private include paths required here ...
                    Path.Combine(ModuleDirectory,"Private")
                }
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core", "CoreUObject", "Engine", "InputCore", "AssetRegistry",
					// ... add other public dependencies that you statically link with here ...
                    "UMG"
                }
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
                    "Slate",
                    "SlateCore",
                    "GameplayTags"
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
