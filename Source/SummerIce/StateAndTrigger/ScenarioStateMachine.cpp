#include "ScenarioStateMachine.h"

UScenarioStateMachine::UScenarioStateMachine(): Super()
{
  BoostStateMahine = std::make_shared<Machine>();
  BoostStateMahine->set_parent(this);
  BoostStateMahine->initiate();
  //BoostStateMahine.process_event(EventMoveToNextState());
}

UScenarioStateMachine* UScenarioStateMachine::Instance()
{
  static UScenarioStateMachine * Inst = nullptr;
  if (!Inst) {
    Inst = NewObject<UScenarioStateMachine>();
    Inst->AddToRoot();
  }
  return Inst;
}
