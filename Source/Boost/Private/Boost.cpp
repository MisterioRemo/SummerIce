// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Boost.h"
#define LOCTEXT_NAMESPACE "FBoostModule"

DEFINE_LOG_CATEGORY(LogBoostModule);

void FBoostModule::StartupModule()
{
  UE_LOG(LogBoostModule, Log, TEXT("BoostModule module Started"));
}

void FBoostModule::ShutdownModule()
{
  UE_LOG(LogBoostModule, Log, TEXT("BoostModule module Stoped"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBoostModule, Boost)
