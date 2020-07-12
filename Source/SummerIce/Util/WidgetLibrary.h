#pragma once

#include "WidgetLibrary.generated.h"

class UUserWidget;

UCLASS()
class SUMMERICE_API UWidgetLibrary : public UObject
{
	GENERATED_BODY()

private:
protected:
public:
	UWidgetLibrary();

private:
protected:
public:
	static TSubclassOf<UUserWidget> DialogBubbleClass;
  static TSubclassOf<UUserWidget> MainInterfaceClass;
};
