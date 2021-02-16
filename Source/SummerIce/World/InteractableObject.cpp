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

	_BodyFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	_BodyFlipbook->SetupAttachment(RootComponent);
  _BodyFlipbook->SetCollisionProfileName(TEXT("NoCollision"));

	_InteractiveFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Buble"));
	_InteractiveFlipbook->SetupAttachment(RootComponent);
  _InteractiveFlipbook->SetCollisionProfileName(TEXT("NoCollision"));

	// Если игрок зашёл в зону действия _BoxComponent, то персонаж может с ним контактировать.
	// Например, открыть дверь или подобрать предмет.
	// Точные размеры задаются в BP.
	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OuterObjectBoxComponent"));
	_BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	_BoxComponent->InitBoxExtent(FVector(16.0f, 20.0f, 16.0f));
	_BoxComponent->SetRelativeLocation(FVector(0.0f, 10.0f, 0.0f));
	_BoxComponent->SetGenerateOverlapEvents(true);
	_BoxComponent->SetupAttachment(RootComponent);
	_BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractableObject::OnPlayerEnterBoxComponent);
	_BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractableObject::OnPlayerExitBoxComponent);	
}

void AInteractableObject::OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
													bool bFromSweep, const FHitResult& SweepResult)
{
	bCanInteract = true;
	OnPopUp(); // вызов в BP, добавление лупы

  if (_EventTiming == EActionTiming::OverlapBegin && OtherActor && OtherActor != this) {
    //UE_LOG(LogTemp, Warning, TEXT("begin\t over = %s,\t other=%s"), *OverlappedActor->GetName(), *OtherActor->GetName());
   //ChooseEvent();
  }
}

void AInteractableObject::OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanInteract = false;
	OnPopUpEnd(); // вызов в BP, удаление лупы

  if (_EventTiming == EActionTiming::OverlapEnd && OtherActor && OtherActor != this) {
    //UE_LOG(LogTemp, Warning, TEXT("end\t over = %s,\t other=%s"), *OverlappedActor->GetName(), *OtherActor->GetName());
   //ChooseEvent();
  }
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


void AInteractableObject::ChooseEvent() const
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