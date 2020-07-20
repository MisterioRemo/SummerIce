#include "MainWidget.h"
#include "SummerIce/World/Lavinia.h"
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

  if (!Player) {
    if (!FindPlayerCharacter())
      return;
  }

  if (bMoving) Player->MoveX(AxisValue);
}

bool UMainWidget::FindPlayerCharacter()
{
  Player = Cast<ALavinia>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
  return Player ? true : false;
}

void UMainWidget::OnPressRightButton()
{
  if (Player->bIsInteracting) {
    Player->ShowNextSpeach();
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
  if (Player->bIsInteracting) {
    Player->ShowPrevSpeach();
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
  if (!Player) {
    if (!FindPlayerCharacter())
      return;
  }
  Player->InteractPressed();
}