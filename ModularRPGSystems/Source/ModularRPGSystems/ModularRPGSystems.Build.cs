// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ModularRPGSystems : ModuleRules
{
	public ModularRPGSystems(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ModularRPGSystems",
			"ModularRPGSystems/Variant_Platforming",
			"ModularRPGSystems/Variant_Platforming/Animation",
			"ModularRPGSystems/Variant_Combat",
			"ModularRPGSystems/Variant_Combat/AI",
			"ModularRPGSystems/Variant_Combat/Animation",
			"ModularRPGSystems/Variant_Combat/Gameplay",
			"ModularRPGSystems/Variant_Combat/Interfaces",
			"ModularRPGSystems/Variant_Combat/UI",
			"ModularRPGSystems/Variant_SideScrolling",
			"ModularRPGSystems/Variant_SideScrolling/AI",
			"ModularRPGSystems/Variant_SideScrolling/Gameplay",
			"ModularRPGSystems/Variant_SideScrolling/Interfaces",
			"ModularRPGSystems/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
