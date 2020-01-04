// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FollowingCamera.generated.h"

class UCameraComponent;

UCLASS()
class SUMMERICE_API AFollowingCamera : public APawn
{
	GENERATED_BODY()

protected:
	bool FollowOwner();
	
public:
	AFollowingCamera();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool WhatShouldWeFollow(APawn * Owner);

private:
	const float CAMERA_DISTANCE_TO_OWNER = 140.0f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	UCameraComponent * _CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	APawn * _Owner = nullptr;
};
