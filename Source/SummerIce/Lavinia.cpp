// Fill out your copyright notice in the Description page of Project Settings.


#include "Lavinia.h"

#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "MyPawnMovementComponent.h"

#include "FollowingCamera.h"

ALavinia::ALavinia()
{
	PrimaryActorTick.bCanEverTick = true;

	// Настройка размеров и положения капсулы происходит в BP,
	// примерные значения: scale (0.2; 0.4; 0.2) и position (2.0; 0.0; -15.0)
	_PlayerBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerBody"));
	_PlayerBody->SetCollisionProfileName(TEXT("Pawn"));
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
	InputComponent->BindAction("Iinteract", EInputEvent::IE_Pressed, this, &ALavinia::InteractPressed);
	InputComponent->BindAction("Iinteract", EInputEvent::IE_Released, this, &ALavinia::InteractReleased);

}

void ALavinia::MoveX(float AxisValue)
{
	if (_MovementComponent && (_MovementComponent->UpdatedComponent == RootComponent)) {
		_MovementComponent->AddInputVector(_PlayerDirection->GetForwardVector() * AxisValue);
	}
}

void ALavinia::InteractPressed()
{
	if (_MovementComponent && (_MovementComponent->UpdatedComponent == RootComponent)) {
		_MovementComponent->Interact(true);
	}
}

void ALavinia::InteractReleased()
{
	if (_MovementComponent && (_MovementComponent->UpdatedComponent == RootComponent)) {
		_MovementComponent->Interact(false);
	}
}

