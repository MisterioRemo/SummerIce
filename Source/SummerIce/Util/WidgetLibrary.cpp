#include "WidgetLibrary.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

TSubclassOf<UUserWidget> UWidgetLibrary::DialogBubbleClass;
TSubclassOf<UUserWidget> UWidgetLibrary::MainInterfaceClass;

UWidgetLibrary::UWidgetLibrary()
{
	// исходная ссылка WidgetBlueprint'/Game/Widget/W_DialogWindow.W_DialogWindow'
	// в ней нужно изменить WidgetBlueprint -> WidgetBlueprintGeneratedClass
	// и *.W_DialogWindow -> *.W_DialogWindow_C

	if (!DialogBubbleClass) {
		static ConstructorHelpers::FClassFinder<UUserWidget> Finded(TEXT("WidgetBlueprintGeneratedClass'/Game/Widget/W_Bubble.W_Bubble_C'"));
		if (Finded.Succeeded())	DialogBubbleClass = Finded.Class;
	}

  if (!MainInterfaceClass) {
    static ConstructorHelpers::FClassFinder<UUserWidget> Finded(TEXT("WidgetBlueprintGeneratedClass'/Game/Widget/W_Main.W_Main_C'"));
    if (Finded.Succeeded())	MainInterfaceClass = Finded.Class;
  }
}