#include "BubbleWidget.h"

UBubbleWidget::UBubbleWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UBubbleWidget::Initialize()
{
	if (!Super::Initialize())
		return false;

	return true;
}

void UBubbleWidget::SetText(const FString & Text)
{
	_Text = Text;
}