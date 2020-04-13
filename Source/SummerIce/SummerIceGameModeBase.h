#pragma once

#include "GameFramework/GameModeBase.h"
#include "SummerIceGameModeBase.generated.h"

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
public:
};
