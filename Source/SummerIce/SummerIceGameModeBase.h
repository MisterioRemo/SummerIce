#pragma once

#include "GameFramework/GameModeBase.h"
#include "SummerIceGameModeBase.generated.h"

class UMainWidget;

UCLASS()
class SUMMERICE_API ASummerIceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
protected:
	virtual void BeginPlay() override;
public:
	int32 GetLevelIndex() const;

private:
protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UMainWidget * _MainUI;

public:
};
