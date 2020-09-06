#include "MainWidget.h"
#include "SummerIce/Control/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

bool UMainWidget::Initialize()
{
  if (!Super::Initialize())
    return false;

  return true;
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
  Super::NativeTick(MyGeometry, InDeltaTime);

  if (!Controller) {
    if (!FindPlayerController())
      return;
  }

  if (bMoving) Controller->MoveX(AxisValue);
}

bool UMainWidget::FindPlayerController()
{
  Controller = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
  return Controller ? true : false;
}

void UMainWidget::OnPressRightButton()
{
  if (Controller->bIsPlayerInteracting) {
    Controller->ShowNextPressed();
    return;
  }

  bMoving = true;
  AxisValue = 1.0;
}
void UMainWidget::OnReleaseRightButton()
{
  bMoving = false;
  AxisValue = 0.0;
}

void UMainWidget::OnPressLeftButton()
{
  if (Controller->bIsPlayerInteracting) {
    Controller->ShowPrevPressed();
    return;
  }

  bMoving = true;
  AxisValue = -1.0;
}
void UMainWidget::OnReleaseLeftButton()
{
  bMoving = false;
  AxisValue = 0.0;
}

void UMainWidget::OnPressInteractButton()
{
  Controller->InteractPressed();
}