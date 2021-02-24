// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mech_Combat : ModuleRules
{
	public Mech_Combat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
