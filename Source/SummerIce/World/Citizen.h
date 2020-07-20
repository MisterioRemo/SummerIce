#pragma once
#include "GameFramework/Pawn.h"
#include "SummerIce/Interface/InteractInterface.h"
#include "Citizen.generated.h"

class UArrowComponent;
class UPaperSpriteComponent;
class UBoxComponent;
class UWidgetComponent;

UCLASS()
class SUMMERICE_API ACitizen : public APawn, public IInteractInterface
{
	GENERATED_BODY()

private:	
  UFUNCTION()
  void OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  UFUNCTION()
  void OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;

	// "Выскакивание" иконки, когда игрок неподалёку
	UFUNCTION(BlueprintImplementableEvent, Category = "Pop up")
	void OnPopUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pop up")
	void OnPopUpEnd();

public:
	ACitizen(const FObjectInitializer& ObjectInitializer);

	// BEGIN InteractInterface
	virtual void ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/) override;
	virtual void HideDialogWidget() override;
	virtual ECharacter GetName() const override; 
	virtual int32 GetDialogId() const override;
	// END InteractInterface

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UArrowComponent * _CitizenDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *_CitizenSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UBoxComponent *_InnerBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UBoxComponent *_OuterBoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent * _DialogBubbleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	ECharacter _CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	int32 _DialogId = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *_InteractiveSprite;

protected:
public:
};
