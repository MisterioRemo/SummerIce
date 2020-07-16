#include "InteractableObject.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Control/MyPlayerController.h"


AInteractableObject::AInteractableObject(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent)
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	_BodySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	_BodySprite->SetupAttachment(RootComponent);
  _BodySprite->SetCollisionProfileName(TEXT("NoCollision"));

	_InteractiveSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Buble"));
	_InteractiveSprite->SetupAttachment(RootComponent);
  _InteractiveSprite->SetCollisionProfileName(TEXT("NoCollision"));

	// Если игрок зашёл в зону действия _BoxComponent, то персонаж может с ним контактировать.
	// Например, открыть дверь или подобрать предмет.
	// Точные размеры задаются в BP.
	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OuterObjectBoxComponent"));
	_BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	_BoxComponent->InitBoxExtent(FVector(16.0f, 100.0f, 16.0f));
	_BoxComponent->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
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
}

void AInteractableObject::OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanInteract = false;
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