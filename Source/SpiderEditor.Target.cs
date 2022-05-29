// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SpiderEditorTarget : TargetRules
{
	public SpiderEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Spider", "GameModule", "SpiderModule" } );

		// Editor에서는 Non-Unity build를 사용하도록 하자.
        bUseUnityBuild = false;
        bUsePCHFiles = false;
    }
}
