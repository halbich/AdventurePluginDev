// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AdventurePluginDev : ModuleRules
{
	public AdventurePluginDev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        PrivateDependencyModuleNames.AddRange(new string[] { "AdventurePluginRuntime", "MessageLog" });
        PrivateIncludePathModuleNames.AddRange(new string[] { "AdventurePluginRuntime" });


        //PublicDependencyModuleNames.AddRange(new string[] { "AdventurePlugin" });
        //PrivateIncludePathModuleNames.AddRange(new string[] { "ProceduralMeshComponent/Runtime", "ProceduralMeshComponent/Public", "ProceduralMeshComponent/Classes", "ProceduralMeshComponent/Private" });
        //PublicIncludePaths.AddRange(new string[] { "ProceduralMeshComponent/Runtime", "ProceduralMeshComponent/Public", "ProceduralMeshComponent/Classes", "ProceduralMeshComponent/Private" });
    }
}
