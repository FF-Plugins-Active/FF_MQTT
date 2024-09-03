// Some copyright should be here...

using System;
using System.IO;
using UnrealBuildTool;

public class FF_MQTT_Sync : ModuleRules
{
	public FF_MQTT_Sync(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;

        if (UnrealTargetPlatform.Win64 == Target.Platform)
        {
            bUseRTTI = true;

			// C Library
            PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_c", "Win64", "include"));

            // Synchronous with SSL
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_c", "Win64", "lib", "paho-mqtt3cs-static.lib"));
        }

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "OpenSSL",
            }
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Json",
                "JsonUtilities",
                "JsonBlueprintUtilities",
            }
			);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
			);
	}
}
