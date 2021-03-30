#pragma once

#include "World/InteractableObject.h"
#include "FakeLight.h"
#include "LightSwitch.generated.h"


UCLASS()
class SUMMERICE_API ALightSwitch: public AInteractableObject
{
  GENERATED_BODY()

public:
  virtual void ChooseEvent() override;
  void SetSwitch(const bool & Value);

protected:
  void BeginPlay() override;

protected:
  UPROPERTY(Category = "Light", EditAnywhere)
  TArray<AFakeLight*> FakeLights;

  UPROPERTY(Category = "Light", EditAnywhere)
  bool bTurnOn;
};
