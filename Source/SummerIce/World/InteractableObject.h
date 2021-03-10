#pragma once

#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "StateAndTrigger/GameEventType.h"
#include "Util/GameItem.h"
#include "InteractableObject.generated.h"

class UPaperFlipbook;
class UPaperFlipbookComponent;
class UBoxComponent;
class UUserWidget;

UCLASS()
class SUMMERICE_API AInteractableObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableObject(const FObjectInitializer& ObjectInitializer);
  EGameItem GetObjectType() const;
  EGameEventType GetEventType() const;
  EActionTiming GetEventTiming() const;
  virtual void ChooseEvent();

	// begin InteractInterface
	virtual void ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/) override;
	virtual void HideDialogWidget() override;
	virtual ECharacter GetName() const override;
	virtual int32 GetDialogId() const override;
	// end InteractInterface

protected:
  void BeginPlay() override;
	// "Выскакивание" иконки, когда игрок неподалёку
	UFUNCTION(BlueprintImplementableEvent, Category = "Pop up")
	void OnPopUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pop up")
	void OnPopUpEnd();

private:
	UFUNCTION()
	void OnPlayerEnterBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnPlayerExitBoxComponent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite)
  EGameEventType _EventType = EGameEventType::NoAction;

  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite,
            meta = (EditCondition = "_EventType == EGameEventType::StartDialog"))
  int32 _DialogId = -1;

  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite,
            meta = (EditCondition = "_EventType != EGameEventType::NoAction"))
  EActionTiming _EventTiming = EActionTiming::None;
  
  UPROPERTY(Category = "Events", EditAnywhere, BlueprintReadWrite,
            meta = (EditCondition = "_EventType == EGameEventType::Teleport"))
  ETeleportLocation _TeleportLocation = ETeleportLocation::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Property")
  UPaperFlipbookComponent * _BodyFlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Property")
  UPaperFlipbookComponent * _InteractiveFlipbookComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property")
	UBoxComponent *_BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
	EGameItem _ObjectType = EGameItem::None;

private:
  UPaperFlipbook * _InteractiveFlipbook;
	bool bCanInteract;  // с данным объектом можно взаимодействовать
  bool bVisible;      // подобрать объект и спрятать его со сцены
};
