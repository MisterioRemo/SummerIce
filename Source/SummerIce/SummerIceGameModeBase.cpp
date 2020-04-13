#include "SummerIceGameModeBase.h"
#include "Util/DialogSystem.h"


void ASummerIceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	DialogSystem::LoadDialogTree(GetLevelIndex());
}


int32 ASummerIceGameModeBase::GetLevelIndex() const
{
	return FCString::Atoi(*GetWorld()->GetName().Mid(0, 2));
}