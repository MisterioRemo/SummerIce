#include "Lavinia.h"

#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

#include "SummerIce/Control/MyPawnMovementComponent.h"
#include "SummerIce/Control/FollowingCamera.h"

#include "Components/WidgetComponent.h"
#include "SummerIce/Widget/WidgetLibrary.h"
#include "SummerIce/Widget/BubbleWidget.h"
#include "SummerIce/Util/DialogSystem.h"

#include "SummerIce/Util/GameEvent.h"
#include "SummerIce/World/InteractableObject.h"


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
	
	_PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayerSprite"));
	_PlayerSprite->SetupAttachment(_PlayerDirection);
  _PlayerSprite->SetCollisionProfileName(TEXT("Pawn"));
  //_PlayerSprite->SetGenerateOverlapEvents(true);  
	_PlayerSprite->OnComponentBeginOverlap.AddDynamic(this, &ALavinia::OnPlayerEnterBoxComponent);
	_PlayerSprite->OnComponentEndOverlap.AddDynamic(this, &ALavinia::OnPlayerExitBoxComponent);

	_MovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MovementComponent"));
	_MovementComponent->UpdatedComponent = RootComponent;

	_DialogBubbleComponent = CreateDefaultSubobject<UWidgetComponent>("DialogBubbleWidget");
	_DialogBubbleComponent->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ALavinia::BeginPlay()
{
	Super::BeginPlay();
	AFollowingCamera * Camera = GetWorld()->SpawnActor<AFollowingCamera>();
	Camera->WhatShouldWeFollow(this);

	if (UWidgetLibrary::DialogBubbleClass) {
		_DialogBubbleComponent->SetWidgetClass(UWidgetLibrary::DialogBubbleClass);
		_DialogBubbleComponent->SetWidgetSpace(EWidgetSpace::Screen);
		_DialogBubbleComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		//_DialogBubbleComponent->SetDrawSize(FVector2D(500.0f, 500.0f));
	}

	DialogSystem::AddSpeaker(Cast<IInteractInterface>(this));
	bIsInteracting = false;

  UGameEvent::Instance()->OnAddItemDelegate.AddDynamic(this, &ALavinia::AddGameItem);
}

void ALavinia::OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
													bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetName().Contains("Outer"))
		DialogSystem::AddSpeaker(Cast<IInteractInterface>(OtherActor));
	else if (OtherComp->GetName().Contains("Inner"))
		DialogSystem::RemoveSpeaker(Cast<IInteractInterface>(OtherActor));
}

void ALavinia::OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
												   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
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

// Called to bind functionality to input
void ALavinia::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &ALavinia::MoveX);
	InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ALavinia::InteractPressed);
	InputComponent->BindAction("ShowNext", EInputEvent::IE_Pressed, this, &ALavinia::ShowNextSpeach);
	InputComponent->BindAction("ShowPrev", EInputEvent::IE_Pressed, this, &ALavinia::ShowPrevSpeach);
}

void ALavinia::MoveX(float AxisValue)
{
	// если игрок в процессе разговора, то он не может двигаться
	if (!bIsInteracting && _MovementComponent
		&& (_MovementComponent->UpdatedComponent == RootComponent)) {
		_MovementComponent->AddInputVector(_PlayerDirection->GetForwardVector() * AxisValue);
	}	
}

void ALavinia::InteractPressed()
{
	bIsInteracting = DialogSystem::StartOrContinueDialog();
}

void ALavinia::ShowNextSpeach()
{
	if (bIsInteracting) DialogSystem::NextNode();	
}

void ALavinia::ShowPrevSpeach()
{
	if (bIsInteracting) DialogSystem::PrevNode();	
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

void ALavinia::HideDialogWidget() {
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


void ALavinia::AddGameItem(AActor * Item)
{
  if (auto IItem = Cast<AInteractableObject>(Item)) {
    auto Type = IItem->GetObjectType();
    if (Type != EGameItem::None)
	    ObtainedItems.AddUnique(Type);
  }
}

bool ALavinia::HasItem(const EGameItem & Item) const
{
	return ObtainedItems.Contains(Item);
}