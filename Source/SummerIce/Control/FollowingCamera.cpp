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
	_CameraComponent->ProjectionMode = ECameraProjectionMode::Perspective;
	_CameraComponent->FieldOfView = 1.0f;
	// С орто-камерой не работает точечный свет
	//_CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	//_CameraComponent->OrthoWidth = 480.0f;
	//_CameraComponent->AspectRatio = 16.0f / 9.0f;

	_CameraComponent->PostProcessSettings.bOverride_BloomIntensity = true;
	_CameraComponent->PostProcessSettings.BloomIntensity = 0.0f;
	_CameraComponent->PostProcessSettings.bOverride_VignetteIntensity = true;
	_CameraComponent->PostProcessSettings.VignetteIntensity = 0.0f;

	_CameraComponent->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	_CameraComponent->SetupAttachment(RootComponent);
}

void AFollowingCamera::BeginPlay()
{
	Super::BeginPlay();

	_CurrentLocation = FVector(0.0, CAMERA_DISTANCE_TO_OWNER, 57.0f);

	// Основная камера
	APlayerController * Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->SetViewTarget(this);
}

void AFollowingCamera::Tick(float DeltaTime)
{
	FollowOwner(DeltaTime);
}

bool AFollowingCamera::WhatShouldWeFollow(APawn * Owner)
{
	return (_Owner = Cast<APawn>(Owner));
}

bool AFollowingCamera::FollowOwner(const float & DeltaTime)
{
	if (_Owner) {
		_CurrentLocation.X = FMath::FInterpTo(_CurrentLocation.X, _Owner->GetActorLocation().X,
											  DeltaTime, CAMERA_INTERP_SPEED);
		SetActorLocation(_CurrentLocation);
		return true;
	}
	return false;
}