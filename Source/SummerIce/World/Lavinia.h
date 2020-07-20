#pragma once

#include "SummerIce/Interface/InteractInterface.h"
#include "GameFramework/Pawn.h"
#include "SummerIce/Util/GameItem.h"
#include "Lavinia.generated.h"

class UArrowComponent;
class UPaperSpriteComponent;
class UCapsuleComponent;
class UMyPawnMovementComponent;
class UWidgetComponent;
class UMainWidget;

UCLASS()
class SUMMERICE_API ALavinia : public APawn, public IInteractInterface
{
  GENERATED_BODY()

  friend class UMainWidget;

private:
	// BEGIN Input
	void MoveX(float AxisValue);
	void InteractPressed();
	void ShowNextSpeach();
	void ShowPrevSpeach();
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

	// BEGIN InteractInterface
	virtual void ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/) override;
	virtual void HideDialogWidget() override;
	virtual ECharacter GetName() const override;
	virtual int32 GetDialogId() const override;
	// END InteractInterface

	void AddGameItem(AActor * Item);
	bool HasItem(const EGameItem & Item) const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UArrowComponent * _PlayerDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *_PlayerSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *_PlayerBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UMyPawnMovementComponent * _MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent * _DialogBubbleComponent;

	bool bIsInteracting;

	TArray<EGameItem> ObtainedItems;

protected:
public:
};
