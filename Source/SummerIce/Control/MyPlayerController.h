#pragma once

#include "SummerIce/Util/GameItem.h"
#include "StateAndTrigger/GameEventType.h"

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UDialogWidget;
class ASummerIceGameModeBase;
class ALavinia;

UCLASS()
class SUMMERICE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
    
  friend class UMainWidget;

public:
  UFUNCTION() void AddGameItemToPlayer(const EGameItem Item);
  UFUNCTION() void RemoveGameItemFromPlayer(const EGameItem Item);
  UFUNCTION() void TeleportPlayerTo(const ETeleportLocation Location);

protected:
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
  virtual void OnPossess(APawn * InPawn) override;

  // Called to bind functionality to input
  virtual void SetupInputComponent() override;

private:
  // BEGIN Input
  void MoveX(float AxisValue);
  void InteractPressed();
  void ShowNextPressed();
  void ShowPrevPressed();
  // END Input

public:
protected:
private:
  ASummerIceGameModeBase * _GameMode;
  ALavinia * _Player;
  bool bIsPlayerInteracting;
};
