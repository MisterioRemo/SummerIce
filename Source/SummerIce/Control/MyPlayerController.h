#pragma once

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UDialogWidget;

UCLASS()
class SUMMERICE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	int32 GetLevelIndex() const;

protected:
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

public:
	void ShowDialogWidget();

private:
	int32 _CurrentLevelIndex;

	UDialogWidget * wDialogBubble;
	TSubclassOf<UDialogWidget> DialogBubbleClass;
protected:
public:
};
