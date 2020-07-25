// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;
using UnrealBuildTool;

public class Boost : ModuleRules
{
    private string ModulePath {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
    }

    public Boost(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "Boost/Public" });

        PrivateIncludePaths.AddRange(new string[] { "Boost/Private" });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            //"CoreUObject",
            //"Engine",
            });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        DynamicallyLoadedModuleNames.AddRange(new string[] { });


        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "BoostLib", "include/boost_1_73_0"));

        PublicSystemIncludePaths.Add(Path.Combine(ThirdPartyPath, "BoostLib", "include/boost_1_73_0"));

        bUseRTTI = true;
        //bEnableExceptions = true;
        //PublicDefinitions.Add("BOOST_NO_RTTI");
        bEnableUndefinedIdentifierWarnings = false;
    }

}
