
using UnrealBuildTool;

public class AdventurePluginDev : ModuleRules
{
    public AdventurePluginDev(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            // default items
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",

            "UMG"   // for spawning widgets
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "AdventurePluginRuntime",   // our plugin
            "SpinePlugin"
        });

        PrivateIncludePathModuleNames.AddRange(new string[] {
            "AdventurePluginRuntime",    // our plugin
            "SpinePlugin"
        });


        //PublicDependencyModuleNames.AddRange(new string[] { "AdventurePlugin" });
        //PrivateIncludePathModuleNames.AddRange(new string[] { "ProceduralMeshComponent/Runtime", "ProceduralMeshComponent/Public", "ProceduralMeshComponent/Classes", "ProceduralMeshComponent/Private" });
        //PublicIncludePaths.AddRange(new string[] { "ProceduralMeshComponent/Runtime", "ProceduralMeshComponent/Public", "ProceduralMeshComponent/Classes", "ProceduralMeshComponent/Private" });
    }
}
