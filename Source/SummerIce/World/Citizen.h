#pragma once

#include "GameFramework/Pawn.h"
#include "Interface/InteractInterface.h"
#include "Citizen.generated.h"

class UArrowComponent;
class UPaperSpriteComponent;
class UBoxComponent;
class UWidgetComponent;

UCLASS()
class SUMMERICE_API ACitizen : public APawn, public IInteractInterface
{
	GENERATED_BODY()

public:
	ACitizen();
	virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* CitizenInputComponent) override;

	// BEGIN InteractInterface
	virtual void ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/) override;
	virtual void HideDialogWidget() override;
	virtual ECharacter GetName() const override; 
	virtual int32 GetDialogId() const override;
	// END InteractInterface
protected:
	virtual void BeginPlay() override;

private:	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UArrowComponent * _CitizenDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *_CitizenSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UBoxComponent *_BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent * _DialogBubbleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	ECharacter _CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Citizen", meta = (AllowPrivateAccess = "true"))
	int32 _DialogId;

protected:
public:
};
