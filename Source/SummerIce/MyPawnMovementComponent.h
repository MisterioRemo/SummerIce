// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "MyPawnMovementComponent.generated.h"


UCLASS()
class SUMMERICE_API UMyPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

private:
	void Sanitize();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Parametrs", meta = (ClampMin = "0.0"))
	float WalkSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Parametrs", meta = (ClampMin = "0.0"))
	float RunSpeed;

public:
	UMyPawnMovementComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void Interact(bool bPressed);

private:
	FVector _MovementInput;

	UPROPERTY()
	uint8 _bIinteract : 1;

public:
};
