#pragma once

#include "GameFramework/Pawn.h"
#include "FollowingCamera.generated.h"

class UCameraComponent;

UCLASS()
class SUMMERICE_API AFollowingCamera : public APawn
{
	GENERATED_BODY()
	
public:
	AFollowingCamera();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool WhatShouldWeFollow(APawn * Owner);

protected:
	bool FollowOwner(const float & DeltaTime);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	UCameraComponent * _CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	APawn * _Owner = nullptr;

private:
	const float CAMERA_INTERP_SPEED = 4.0f;

	FVector _CurrentLocation;  
};
