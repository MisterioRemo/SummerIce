#pragma once

#include "SummerIce/Interface/InteractInterface.h"
#include "GameFramework/Pawn.h"
#include "SummerIce/Util/GameItem.h"
#include "Lavinia.generated.h"

class UArrowComponent;
class UPaperFlipbookComponent;
class UCapsuleComponent;
class UMyPawnMovementComponent;
class UWidgetComponent;
class UMainWidget;
class AMyPlayerController;

UCLASS()
class SUMMERICE_API ALavinia: public APawn, public IInteractInterface
{
  GENERATED_BODY()
  
  friend class AMyPlayerController;

public:
  ALavinia(const FObjectInitializer& ObjectInitializer);

  bool HasItem(const EGameItem & Item) const;

  // BEGIN InteractInterface
  virtual void ShowDialogWidget(const FString * Text /* = nullptr*/, const bool & bCanChooseLine /* = false*/) override;
  virtual void HideDialogWidget() override;
  virtual ECharacter GetName() const override;
  virtual int32 GetDialogId() const override;
  // END InteractInterface

protected:
  virtual void Tick(float DeltaTime) override;
  virtual void BeginPlay() override;
  virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
  void Move(const float & AxisValue);

  UFUNCTION()
  void OnPlayerEnterBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  UFUNCTION()
  void OnPlayerExitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
  AMyPlayerController * _Controller;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
  UArrowComponent * _PlayerDirection;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
  UPaperFlipbookComponent *_PlayerFlipbook;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
  UCapsuleComponent *_PlayerBody;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
  UMyPawnMovementComponent * _MovementComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lavinia", meta = (AllowPrivateAccess = "true"))
  UWidgetComponent * _DialogBubbleComponent;

protected:
  TArray<EGameItem> ObtainedItems;
};
