#pragma once

#include "GameFramework/Pawn.h"
#include "Lavinia.generated.h"

class UArrowComponent;
class UPaperSpriteComponent;
class UCapsuleComponent;
class UMyPawnMovementComponent;
class AInteractableObject;


UCLASS()
class SUMMERICE_API ALavinia : public APawn
{
	GENERATED_BODY()
	friend class AInteractableObject;

private:
	// BEGIN Input
	void MoveX(float AxisValue);
	void InteractPressed();
	void InteractReleased();
	// END Input

	UFUNCTION()
	void OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

public:
	ALavinia(const FObjectInitializer& ObjectInitializer);
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

	// Объект класса AInteractableObject, с которым можно взоимодейтсовать через Interact input 
	AInteractableObject *_InteractableObject;

protected:

	
};
