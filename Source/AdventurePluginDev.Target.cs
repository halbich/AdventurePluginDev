
using UnrealBuildTool;
using System.Collections.Generic;

public class AdventurePluginDevTarget : TargetRules
{
	public AdventurePluginDevTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("AdventurePluginDev");
        ExtraModuleNames.Add("SpinePlugin");
	}
}
