#pragma once

#include "GameFramework/GameModeBase.h"
#include "StateAndTrigger/SpawnPoint.h"
#include "SummerIceGameModeBase.generated.h"

class UMainWidget;

UCLASS()
class SUMMERICE_API ASummerIceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	int32 GetLevelIndex() const;
  const ASpawnPoint* GetSpawnPoint(const ETeleportLocation & LocationName) const;

protected:
	virtual void BeginPlay() override;

private:
  void FindAllSpawnPoint();

public:
protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UMainWidget * _MainUI;

private:
  TMap<ETeleportLocation, ASpawnPoint*> _SpawnPointsMap;
};
