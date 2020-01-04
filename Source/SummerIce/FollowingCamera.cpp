#include "FollowingCamera.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

#include "Camera/CameraComponent.h"

AFollowingCamera::AFollowingCamera()
{
	if (!RootComponent)
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	_CameraComponent->bUsePawnControlRotation = false;
	_CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	_CameraComponent->OrthoWidth = 480.0f;
	_CameraComponent->AspectRatio = 16.0f / 9.0f;
	_CameraComponent->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	_CameraComponent->SetupAttachment(RootComponent);
}

void AFollowingCamera::BeginPlay()
{
	Super::BeginPlay();

	// Основная камера
	APlayerController * Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetViewTarget(this);
}

void AFollowingCamera::Tick(float DeltaTime)
{
	FollowOwner();
}

bool AFollowingCamera::WhatShouldWeFollow(APawn * Owner)
{
	return (_Owner = Cast<APawn>(Owner));
}

bool AFollowingCamera::FollowOwner()
{
	if (_Owner) {
		FVector Loc = _Owner->GetActorLocation();
		Loc.Y += CAMERA_DISTANCE_TO_OWNER;
		Loc.Z = -135.0f;
		SetActorLocation(Loc);
		return true;
	}
	return false;
}