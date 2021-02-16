#include "MyPlayerController.h"
#include "SummerIce.h"
#include "World/Lavinia.h"
#include "World/InteractableObject.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "StateAndTrigger/GameEvent.h"
#include "SummerIceGameModeBase.h"

#include "Util/DialogSystem.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void AMyPlayerController::OnPossess(APawn * InPawn)
{
  Super::OnPossess(InPawn);
  _Player = Cast<ALavinia>(InPawn);
  check(_Player);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
  _GameMode = Cast<ASummerIceGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
  bIsPlayerInteracting = false;

  UGameEvent::Instance()->OnAddItemDelegate.AddDynamic(this, &AMyPlayerController::AddGameItemToPlayer);
  UGameEvent::Instance()->OnRemoveItemDelegate.AddDynamic(this, &AMyPlayerController::RemoveGameItemFromPlayer);
  UGameEvent::Instance()->OnTeleportPlayerDelegate.AddDynamic(this, &AMyPlayerController::TeleportPlayerTo);
}

void AMyPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();
  InputComponent->BindAxis("MoveX", this, &AMyPlayerController::MoveX);
  InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AMyPlayerController::InteractPressed);
  InputComponent->BindAction("ShowNext", EInputEvent::IE_Pressed, this, &AMyPlayerController::ShowNextPressed);
  InputComponent->BindAction("ShowPrev", EInputEvent::IE_Pressed, this, &AMyPlayerController::ShowPrevPressed);
}

// BEGIN Input
void AMyPlayerController::MoveX(float AxisValue)
{
	// если игрок в процессе разговора, то он не может двигаться
  if (!bIsPlayerInteracting) _Player->Move(AxisValue);
}

void AMyPlayerController::InteractPressed()
{
  if (!bIsPlayerInteracting && _ObjectPlayerInteratWith
      && _ObjectPlayerInteratWith->GetEventTiming() == EActionTiming::PressInteractBtn) {
    _ObjectPlayerInteratWith->ChooseEvent();
  }

  bIsPlayerInteracting = DialogSystem::StartOrContinueDialog();
}

void AMyPlayerController::ShowNextPressed()
{
  if (bIsPlayerInteracting) DialogSystem::NextNode();
}

void AMyPlayerController::ShowPrevPressed()
{
  if (bIsPlayerInteracting) DialogSystem::PrevNode();  
}

// END Input

void AMyPlayerController::AddGameItemToPlayer(const EGameItem Item)
{
  if (Item != EGameItem::None)
    _Player->ObtainedItems.AddUnique(Item);  
}

void AMyPlayerController::RemoveGameItemFromPlayer(const EGameItem Item)
{
  if (Item != EGameItem::None)
    _Player->ObtainedItems.Remove(Item);
}

void AMyPlayerController::TeleportPlayerTo(const ETeleportLocation Location)
{
  if (Location == ETeleportLocation::None)
    return;

  if (auto SpawnPoint = _GameMode->GetSpawnPoint(Location)) {
    _Player->SetActorLocation(SpawnPoint->GetPointLocation());
    //rotate lavinia
  }
  
}

void AMyPlayerController::SetInteractableObject(AActor * Object)
{
  _ObjectPlayerInteratWith = Cast<AInteractableObject>(Object);
}