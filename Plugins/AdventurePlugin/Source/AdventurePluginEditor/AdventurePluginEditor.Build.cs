using System.IO;
namespace UnrealBuildTool.Rules
{
    public class AdventurePluginEditor : ModuleRules
    {
        public AdventurePluginEditor(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
                new string[] {
                    Path.Combine(ModuleDirectory,"Public")
					// ... add public include paths required here ...
				}
                );

            PrivateIncludePaths.AddRange(
                new string[] {
                    Path.Combine(ModuleDirectory, "Private")
					//"Developer/AdventurePluginEditor/Private",
					// ... add other private include paths required here ...
				}
                );

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
					// ... add other public dependencies that you statically link with here ...
                    "AdventurePluginRuntime"
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
                    "GraphEditor",
                    "EditorStyle",
                    "LevelEditor",
                    "CoreUObject",
                    "Engine",
                    "Slate",
                    "SlateCore",
                    "AssetTools",
                    "PropertyEditor",
                    "Kismet",
                    "KismetWidgets",
                    "ApplicationCore",
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