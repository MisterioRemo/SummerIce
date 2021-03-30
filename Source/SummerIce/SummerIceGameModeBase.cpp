#include "SummerIceGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/MainWidget.h"
#include "Widget/WidgetLibrary.h"
#include "Util/DialogSystem.h"

#include "EngineUtils.h"

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
  for (TActorIterator<ASpawnPoint> It(GetWorld()); It; ++It) {
    _SpawnPointsMap.Emplace((*It)->GetTeleportLocationName(), *It);
  }
}

const ASpawnPoint* ASummerIceGameModeBase::GetSpawnPoint(const ETeleportLocation & LocationName) const
{
  if (const auto Elem = _SpawnPointsMap.Find(LocationName))
    return *Elem;
  else
    return nullptr;
}
