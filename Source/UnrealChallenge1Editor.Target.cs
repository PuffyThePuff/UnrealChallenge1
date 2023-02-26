// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealChallenge1EditorTarget : TargetRules
{
	public UnrealChallenge1EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("UnrealChallenge1");
	}
}
