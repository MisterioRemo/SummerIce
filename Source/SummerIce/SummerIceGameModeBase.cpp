#include "SummerIceGameModeBase.h"
#include "Widget/MainWidget.h"
#include "Util/WidgetLibrary.h"
#include "Util/DialogSystem.h"

void ASummerIceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	DialogSystem::LoadDialogTree(GetLevelIndex());

  if (UWidgetLibrary::MainInterfaceClass && !_MainUI) {
    _MainUI = CreateWidget<UMainWidget>(GetWorld(), UWidgetLibrary::MainInterfaceClass);
    if (_MainUI) {
      _MainUI->AddToViewport();
      _MainUI->SetVisibility(ESlateVisibility::Visible);
    }
  }
}


int32 ASummerIceGameModeBase::GetLevelIndex() const
{
	return FCString::Atoi(*GetWorld()->GetName().Mid(0, 2));
}