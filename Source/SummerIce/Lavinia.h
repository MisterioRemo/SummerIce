// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Lavinia.generated.h"

class UArrowComponent;
class UPaperSpriteComponent;
class UCapsuleComponent;
class UMyPawnMovementComponent;



UCLASS()
class SUMMERICE_API ALavinia : public APawn
{
	GENERATED_BODY()

private:
	// BEGIN Input
	void MoveX(float AxisValue);
	void InteractPressed();
	void InteractReleased();
	// END Input

protected:
	virtual void BeginPlay() override;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

public:
	ALavinia();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UArrowComponent * _PlayerDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *_PlayerSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *_PlayerBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UMyPawnMovementComponent * _MovementComponent;

protected:

	
};
