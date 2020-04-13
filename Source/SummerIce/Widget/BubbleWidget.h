#pragma once

#include "Blueprint/UserWidget.h"
#include "BubbleWidget.generated.h"


UCLASS()
class SUMMERICE_API UBubbleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
protected:
	virtual bool Initialize() override;
public:
	UBubbleWidget(const FObjectInitializer& ObjectInitializer);
	void SetText(const FString & Text);

private:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Text")
	FString _Text;

public:
};
