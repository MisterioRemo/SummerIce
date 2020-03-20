#include "Lavinia.h"

#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

#include "Control/MyPawnMovementComponent.h"
#include "Control/FollowingCamera.h"

#include "World/InteractableObject.h"
#include "Interface/InteractInterface.h"

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

	_MovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MovementComponent"));
	_MovementComponent->UpdatedComponent = RootComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void ALavinia::BeginPlay()
{
	Super::BeginPlay();
	AFollowingCamera * Camera = GetWorld()->SpawnActor<AFollowingCamera>();
	Camera->WhatShouldWeFollow(this);

	// AddDynamic должно вызываться единожды для одной функции,
	// но OnComponentEndOverlap не работает, если "связывать" в конструкторе объекта
	_PlayerSprite->OnComponentBeginOverlap.RemoveDynamic(this, &ALavinia::OnPlayerEnterBoxComponent);
	_PlayerSprite->OnComponentEndOverlap.RemoveDynamic(this, &ALavinia::OnPlayerExitBoxComponent);

	_PlayerSprite->OnComponentBeginOverlap.AddDynamic(this, &ALavinia::OnPlayerEnterBoxComponent);
	_PlayerSprite->OnComponentEndOverlap.AddDynamic(this, &ALavinia::OnPlayerExitBoxComponent);
}

void ALavinia::OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
													bool bFromSweep, const FHitResult& SweepResult)
{
	_InteractableObject = Cast<AInteractableObject>(OtherActor);
}

void ALavinia::OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
												   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_InteractableObject = nullptr;
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
	InputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &ALavinia::InteractReleased);

}

void ALavinia::MoveX(float AxisValue)
{
	if (_MovementComponent && (_MovementComponent->UpdatedComponent == RootComponent)) {
		_MovementComponent->AddInputVector(_PlayerDirection->GetForwardVector() * AxisValue);
	}
}

void ALavinia::InteractPressed()
{
	if (_InteractableObject) {
		_InteractableObject->ShowDialogWidget();
	}
}

void ALavinia::InteractReleased()
{	
}