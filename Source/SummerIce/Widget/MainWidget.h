#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class AMyPlayerController;

UCLASS()
class SUMMERICE_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

private:
  bool FindPlayerController();

protected:
  virtual bool Initialize() override;
  virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

  UFUNCTION(BlueprintCallable, Category = "Button Event")
  void OnPressRightButton();
  UFUNCTION(BlueprintCallable, Category = "Button Event")
  void OnReleaseRightButton();

  UFUNCTION(BlueprintCallable, Category = "Button Event")
  void OnPressLeftButton();
  UFUNCTION(BlueprintCallable, Category = "Button Event")
  void OnReleaseLeftButton();

  UFUNCTION(BlueprintCallable, Category = "Button Event")
  void OnPressInteractButton();

public:

private:
  AMyPlayerController * Controller;

  bool bMoving;
  float AxisValue;

protected:
public:
};
