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
  void SetArrowsVisibility(const bool & IsVisible);
  void SetRightArrowVisibility(const bool & IsVisible);
  void SetLeftArrowVisibility(const bool & IsVisible);

private:
  UWidget * _RightArrow;
  UWidget * _LeftArrow;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Text")
	FString _Text;

public:
};
