#include "ScenarioStateMachine.h"

UScenarioStateMachine::UScenarioStateMachine(): Super()
{ }

UScenarioStateMachine* UScenarioStateMachine::Instance()
{
  static UScenarioStateMachine * Inst = nullptr;
  if (!Inst) {
    Inst = NewObject<UScenarioStateMachine>();
    Inst->AddToRoot();
  }
  return Inst;
}
