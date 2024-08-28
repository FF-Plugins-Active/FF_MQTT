// Some copyright should be here...

using System;
using System.IO;
using UnrealBuildTool;

public class FF_MQTT : ModuleRules
{
	public FF_MQTT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;

        if (UnrealTargetPlatform.Win64 == Target.Platform)
        {
            bUseRTTI = true;

			// C Library
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_c", "Win64", "include"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_c", "Win64", "lib", "paho-mqtt3as-static.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_c", "Win64", "lib", "paho-mqtt3a-static.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_c", "Win64", "lib", "paho-mqtt3cs-static.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_c", "Win64", "lib", "paho-mqtt3c-static.lib"));

            // CPP Library
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_cpp", "Win64", "include"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "paho_cpp", "Win64", "lib", "paho-mqttpp3-static.lib"));
        }

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "OpenSSL",
                "FF_MBedTLS",
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
