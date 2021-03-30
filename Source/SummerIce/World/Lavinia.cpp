#include "Lavinia.h"
#include "SummerIce.h"
#include "Kismet/GameplayStatics.h"
#include "SummerIceGameModeBase.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

#include "Control/MyPlayerController.h"
#include "Control/MyPawnMovementComponent.h"
#include "Control/FollowingCamera.h"

#include "Components/WidgetComponent.h"
#include "Widget/WidgetLibrary.h"
#include "Widget/BubbleWidget.h"
#include "Util/DialogSystem.h"

#include "World/InteractableObject.h"


ALavinia::ALavinia(const FObjectInitializer& ObjectInitializer)
  :Super(ObjectInitializer)
{
  PrimaryActorTick.bCanEverTick = true;

  // Настройка размеров и положения капсулы происходит в BP,
  // примерные значения: scale (0.2; 0.4; 0.2) и position (2.0; 0.0; -15.0)
  _PlayerBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerBody"));
  _PlayerBody->SetCollisionProfileName(TEXT("Pawn"));
  _PlayerBody->SetGenerateOverlapEvents(true);
  SetRootComponent(_PlayerBody);

  _PlayerDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerDirection"));
  _PlayerDirection->SetupAttachment(RootComponent);

  _PlayerFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerFlipbook"));
  _PlayerFlipbook->SetupAttachment(_PlayerDirection);
  _PlayerFlipbook->SetCollisionProfileName(TEXT("Pawn"));
  _PlayerFlipbook->SetGenerateOverlapEvents(true);

  _MovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MovementComponent"));
  _MovementComponent->UpdatedComponent = RootComponent;

  _DialogBubbleComponent = CreateDefaultSubobject<UWidgetComponent>("DialogBubbleWidget");
  _DialogBubbleComponent->SetupAttachment(RootComponent);

  AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ALavinia::BeginPlay()
{
  Super::BeginPlay();
  _Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
  check(_Controller);

  AFollowingCamera * Camera = GetWorld()->SpawnActor<AFollowingCamera>();
  Camera->WhatShouldWeFollow(this);

  if (UWidgetLibrary::DialogBubbleClass) {
    _DialogBubbleComponent->SetWidgetClass(UWidgetLibrary::DialogBubbleClass);
    _DialogBubbleComponent->SetWidgetSpace(EWidgetSpace::Screen);
    _DialogBubbleComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
    //_DialogBubbleComponent->SetDrawSize(FVector2D(500.0f, 500.0f));
  }
  _PlayerFlipbook->OnComponentBeginOverlap.AddDynamic(this, &ALavinia::OnPlayerEnterBox);
  _PlayerFlipbook->OnComponentEndOverlap.AddDynamic(this, &ALavinia::OnPlayerExitBox);

  DialogSystem::AddSpeaker(Cast<IInteractInterface>(this));
}

void ALavinia::OnPlayerEnterBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                bool bFromSweep, const FHitResult& SweepResult)
{
  _Controller->SetInteractableObject(OtherActor);
  if (OtherComp->GetName().Contains("Outer"))
    DialogSystem::AddSpeaker(Cast<IInteractInterface>(OtherActor));
  else if (OtherComp->GetName().Contains("Inner"))
    DialogSystem::RemoveSpeaker(Cast<IInteractInterface>(OtherActor));
}

void ALavinia::OnPlayerExitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  _Controller->SetInteractableObject(nullptr);
  if (OtherComp->GetName().Contains("Outer"))
    DialogSystem::RemoveSpeaker(Cast<IInteractInterface>(OtherActor));
  else if (OtherComp->GetName().Contains("Inner"))
    DialogSystem::AddSpeaker(Cast<IInteractInterface>(OtherActor));
}

UPawnMovementComponent* ALavinia::GetMovementComponent() const
{
  return _MovementComponent;
}

void ALavinia::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void ALavinia::Move(const float & AxisValue)
{
  if (_MovementComponent && _MovementComponent->UpdatedComponent == RootComponent) {
    _MovementComponent->AddInputVector(_PlayerDirection->GetForwardVector() * AxisValue);
  }
}

bool ALavinia::HasItem(const EGameItem & Item) const
{
  return ObtainedItems.Contains(Item);
}

// BEGIN InteractInterface
void ALavinia::ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/)
{
  auto Widget = Cast<UBubbleWidget>(_DialogBubbleComponent->GetUserWidgetObject());
  if (Text && Widget) {
    Widget->SetVisibility(ESlateVisibility::Visible);
    Widget->SetArrowsVisibility(bCanChooseLine);
    Widget->SetText(*Text);
  }
}

void ALavinia::HideDialogWidget()
{
  _DialogBubbleComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
}

ECharacter ALavinia::GetName() const
{
  return ECharacter::Lavinia;
}

int32 ALavinia::GetDialogId() const
{
  return -1;
}
// END InteractInterface
