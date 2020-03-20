#include "MyPlayerController.h"

#include "UObject/ConstructorHelpers.h"
#include "Widget/DialogWidget.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!DialogBubbleClass) {
		// исходная ссылка WidgetBlueprint'/Game/Widget/W_DialogBubble.W_DialogBubble'
		// в ней нужно изменить WidgetBlueprint -> WidgetBlueprintGeneratedClass
		// и W_DialogBubble -> W_DialogBubble_C
		static ConstructorHelpers::FClassFinder<UUserWidget> Finded(TEXT("WidgetBlueprintGeneratedClass'/Game/Widget/W_DialogBubble.W_DialogBubble_C'"));
		if (Finded.Succeeded())
			DialogBubbleClass = Finded.Class;
	}
}

int32 AMyPlayerController::GetLevelIndex() const
{
	return FCString::Atoi(*GetWorld()->GetName().Mid(0, 2));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	_CurrentLevelIndex = GetLevelIndex();

	if (DialogBubbleClass) {
		wDialogBubble = CreateWidget<UDialogWidget>(this, DialogBubbleClass);
		wDialogBubble->AddToViewport();
		wDialogBubble->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMyPlayerController::ShowDialogWidget()
{
	if (wDialogBubble) {
		bShowMouseCursor = true;
		wDialogBubble->StartDialog(_CurrentLevelIndex, 0);		
	}
}
