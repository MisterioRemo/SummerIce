#pragma once

#include "GameFramework/Pawn.h"
#include "FollowingCamera.generated.h"

class UCameraComponent;

UCLASS()
class SUMMERICE_API AFollowingCamera : public APawn
{
	GENERATED_BODY()

protected:
	bool FollowOwner(const float & DeltaTime);
	
public:
	AFollowingCamera();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool WhatShouldWeFollow(APawn * Owner);

private:
	const float CAMERA_DISTANCE_TO_OWNER = 25000.0f;
	const float CAMERA_INTERP_SPEED = 4.0f;

	FVector _CurrentLocation;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	UCameraComponent * _CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	APawn * _Owner = nullptr;
};
