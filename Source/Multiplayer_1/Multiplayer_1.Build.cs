// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Multiplayer_1 : ModuleRules
{
	public Multiplayer_1(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
                                                            "Http", "Json", "JsonUtilities",
                                                            "UMG" });

        PublicDependencyModuleNames.Add("GameplayAbilities");
        PublicDependencyModuleNames.Add("OnlineSubsystem");
        PublicDependencyModuleNames.Add("GameplayAbilities");
        PublicDependencyModuleNames.Add("GameplayTags");
        PublicDependencyModuleNames.Add("GameplayTasks");

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
