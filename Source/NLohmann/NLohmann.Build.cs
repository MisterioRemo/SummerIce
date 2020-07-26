// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;
using UnrealBuildTool;

public class NLohmann : ModuleRules
{
    public NLohmann(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "NLohmann/Public" });

        PrivateIncludePaths.AddRange(new string[] { "NLohmann/Private" });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            //"CoreUObject",
            //"Engine",
            });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        DynamicallyLoadedModuleNames.AddRange(new string[] { });
    }

}
