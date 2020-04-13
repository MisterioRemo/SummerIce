#pragma once

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UDialogWidget;

UCLASS()
class SUMMERICE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
protected:
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

public:

private:
protected:
public:
};
