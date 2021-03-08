#include "LightSwitch.h"

void ALightSwitch::BeginPlay()
{
  Super::BeginPlay();
  _EventType = EGameEventType::Other;
  _EventTiming = EActionTiming::PressInteractBtn;
}

void ALightSwitch::ChooseEvent()
{
  bTurnOn = !bTurnOn;
  for (const auto Light : FakeLights) {
    Light->SwitchLightState(bTurnOn);
  }
}

void ALightSwitch::SetSwitch(const bool & Value)
{
  bTurnOn = Value;
}