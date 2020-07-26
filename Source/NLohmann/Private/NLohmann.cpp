// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NLohmann.h"
#define LOCTEXT_NAMESPACE "FNLohmannModule"

DEFINE_LOG_CATEGORY(LogNLohmannModule);

void FNLohmannModule::StartupModule()
{
  UE_LOG(LogNLohmannModule, Log, TEXT("NLohmannModule module Started"));
}

void FNLohmannModule::ShutdownModule()
{
  UE_LOG(LogNLohmannModule, Log, TEXT("NLohmannModule module Stoped"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNLohmannModule, NLohmann)
