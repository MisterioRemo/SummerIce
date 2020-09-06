#include "SummerIceGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/MainWidget.h"
#include "Widget/WidgetLibrary.h"
#include "Util/DialogSystem.h"

void ASummerIceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	DialogSystem::LoadDialogTree(GetLevelIndex());
  FindAllSpawnPoint();

  if (UWidgetLibrary::MainInterfaceClass && !_MainUI) {
    _MainUI = CreateWidget<UMainWidget>(GetWorld(), UWidgetLibrary::MainInterfaceClass);
    if (_MainUI) {
      _MainUI->AddToViewport();
      _MainUI->SetVisibility(ESlateVisibility::Visible);
    }
  }
}


int32 ASummerIceGameModeBase::GetLevelIndex() const
{
	return FCString::Atoi(*GetWorld()->GetName().Mid(0, 2));
}


void ASummerIceGameModeBase::FindAllSpawnPoint()
{
  TArray<AActor*> Array;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), Array);

  for (auto Actor : Array) {
    if (auto SpawnPoint = Cast<ASpawnPoint>(Actor)) 
      _SpawnPointsMap.Emplace(SpawnPoint->GetTeleportLocationName(), SpawnPoint);    
  }
}

const ASpawnPoint* ASummerIceGameModeBase::GetSpawnPoint(const ETeleportLocation & LocationName) const
{
  return *_SpawnPointsMap.Find(LocationName);
}