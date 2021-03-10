#include "LightSwitch.h"
#include "PaperFlipbookComponent.h"

void ALightSwitch::BeginPlay()
{
  Super::BeginPlay();
  _EventType = EGameEventType::Other;
  _EventTiming = EActionTiming::PressInteractBtn;

  // применить настройки bTurnOn из эдитора
  bTurnOn = !bTurnOn;
  ChooseEvent();
}

void ALightSwitch::ChooseEvent()
{
  bTurnOn = !bTurnOn;
  _BodyFlipbookComponent->SetPlaybackPositionInFrames(bTurnOn ? 0 : 1, false);
  for (const auto Light : FakeLights) {
    Light->SwitchLightState(bTurnOn);
  }
}

void ALightSwitch::SetSwitch(const bool & Value)
{
  bTurnOn = Value;
}