
using UnrealBuildTool;
using System.Collections.Generic;

public class AdventurePluginDevEditorTarget : TargetRules
{
	public AdventurePluginDevEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("AdventurePluginDev");
	}
}
