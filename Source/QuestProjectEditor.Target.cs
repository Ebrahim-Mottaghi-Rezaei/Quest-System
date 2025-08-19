// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved 2025.

using UnrealBuildTool;
using System.Collections.Generic;

public class QuestProjectEditorTarget : TargetRules
{
	public QuestProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "QuestProject" } );
	}
}
