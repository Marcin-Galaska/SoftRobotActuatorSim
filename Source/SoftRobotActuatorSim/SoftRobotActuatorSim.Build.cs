// Copyright Marcin Gałąska, 2024.

using UnrealBuildTool;

public class SoftRobotActuatorSim : ModuleRules
{
	public SoftRobotActuatorSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
