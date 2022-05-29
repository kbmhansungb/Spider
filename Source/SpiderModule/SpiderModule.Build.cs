// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpiderModule : ModuleRules
{
	public SpiderModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicDependencyModuleNames.AddRange(new string[] { "BlueprintGraph", "AnimGraph", "AnimGraphRuntime" });
	}
}
