#pragma once

#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "Util/GameItem.h"
#include "InteractableObject.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
class UUserWidget;

UCLASS()
class SUMMERICE_API AInteractableObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// "Выскакивание" иконки, когда игрок неподалёку
	UFUNCTION(BlueprintImplementableEvent, Category = "Pop up")
	void OnPopUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pop up")
	void OnPopUpEnd();
	
public:	
	AInteractableObject(const FObjectInitializer& ObjectInitializer);
  EGameItem GetObjectType() const;

	// begin InteractInterface
	virtual void ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/) override;
	virtual void HideDialogWidget() override;
	virtual ECharacter GetName() const override;
	virtual int32 GetDialogId() const override;
	// end InteractInterface
  
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *_BodySprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *_InteractiveSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	UBoxComponent *_BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
	EGameItem _ObjectType = EGameItem::None;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property", meta = (AllowPrivateAccess = "true"))
  int32 _DialogId;
	
	bool bCanInteract;  // с данным объектом можно взаимодействовать
  bool bVisible;      // подобрать объект и спрятать его со сцены
  
protected:
};
