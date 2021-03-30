#include "InteractableObject.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Control/MyPlayerController.h"

#include "StateAndTrigger/GameEvent.h"


AInteractableObject::AInteractableObject(const FObjectInitializer& ObjectInitializer)
  :Super(ObjectInitializer)
{
  PrimaryActorTick.bCanEverTick = false;

  if (!RootComponent)
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

  _BodyFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
  _BodyFlipbookComponent->SetupAttachment(RootComponent);
  _BodyFlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));

  _InteractiveFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Buble"));
  _InteractiveFlipbookComponent->SetupAttachment(RootComponent);
  _InteractiveFlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));

  // Если игрок зашёл в зону действия _BoxComponent, то персонаж может с ним контактировать.
  // Например, открыть дверь или подобрать предмет.
  // Точные размеры задаются в BP.
  _BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OuterObjectBoxComponent"));
  _BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
  _BoxComponent->InitBoxExtent(FVector(16.0f, 20.0f, 16.0f));
  _BoxComponent->SetRelativeLocation(FVector(0.0f, 10.0f, 0.0f));
  _BoxComponent->SetGenerateOverlapEvents(true);
  _BoxComponent->SetupAttachment(RootComponent);
}

void AInteractableObject::BeginPlay()
{
  Super::BeginPlay();

  _InteractiveFlipbook = _InteractiveFlipbookComponent->GetFlipbook();
  _InteractiveFlipbookComponent->SetFlipbook(nullptr);

  _BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractableObject::OnPlayerEnterBoxComponent);
  _BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractableObject::OnPlayerExitBoxComponent);
}

void AInteractableObject::OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                    bool bFromSweep, const FHitResult& SweepResult)
{
  bCanInteract = true;
  _InteractiveFlipbookComponent->SetFlipbook(_InteractiveFlipbook);
  OnPopUp(); // вызов в BP, добавление лупы
}

void AInteractableObject::OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  bCanInteract = false;
  _InteractiveFlipbookComponent->SetFlipbook(nullptr);
  OnPopUpEnd(); // вызов в BP, удаление лупы
}


// begin InteractInterface
void AInteractableObject::ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/)
{
}
void AInteractableObject::HideDialogWidget()
{
}

ECharacter AInteractableObject::GetName() const
{
  return ECharacter::Object;
}

int32 AInteractableObject::GetDialogId() const
{
  return _DialogId;
}
// end InteractInterface

EGameItem AInteractableObject::GetObjectType() const
{
  return _ObjectType;
}

EGameEventType AInteractableObject::GetEventType() const
{
  return _EventType;
}

EActionTiming AInteractableObject::GetEventTiming() const
{
  return _EventTiming;
}


void AInteractableObject::ChooseEvent()
{
  switch (_EventType) {
    case EGameEventType::NoAction:
      break;
    case EGameEventType::TakeItem:
      UGameEvent::Instance()->OnAddItemDelegate.Broadcast(_ObjectType);
      break;
    case EGameEventType::RemoveItem:
      UGameEvent::Instance()->OnRemoveItemDelegate.Broadcast(_ObjectType);
      break;
    case EGameEventType::Teleport:
      UGameEvent::Instance()->OnTeleportPlayerDelegate.Broadcast(_TeleportLocation);
      break;
    default:
      break;
  }
}
