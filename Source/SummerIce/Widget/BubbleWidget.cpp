#include "BubbleWidget.h"
#include "Blueprint/WidgetTree.h"

UBubbleWidget::UBubbleWidget(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
}

bool UBubbleWidget::Initialize()
{
  if (!Super::Initialize())
    return false;

  _RightArrow = WidgetTree->FindWidget(TEXT("Image_arrow_right"));
  _LeftArrow = WidgetTree->FindWidget(TEXT("Image_arrow_left"));

  _RightArrow->SetVisibility(ESlateVisibility::Hidden);
  _LeftArrow->SetVisibility(ESlateVisibility::Hidden);

  return true;
}


void UBubbleWidget::SetText(const FString & Text)
{
  _Text = Text;
}

void UBubbleWidget::SetArrowsVisibility(const bool & IsVisible)
{
  SetRightArrowVisibility(IsVisible);
  SetLeftArrowVisibility(IsVisible);
}

void UBubbleWidget::SetRightArrowVisibility(const bool & IsVisible)
{
  _RightArrow->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UBubbleWidget::SetLeftArrowVisibility(const bool & IsVisible)
{
  _LeftArrow->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}