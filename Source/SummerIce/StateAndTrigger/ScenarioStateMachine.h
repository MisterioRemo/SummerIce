#pragma once

#include "CoreMinimal.h"
#include "ScenarioState.h"
#include <memory>

#include "ScenarioStateMachine.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetStateDelegate, ScenarioState, State);

struct Machine;

UCLASS()
class SUMMERICE_API UScenarioStateMachine: public UObject
{
  GENERATED_BODY()

private:
  UScenarioStateMachine();

protected:
public:
  UScenarioStateMachine * Instance();

private:
  std::shared_ptr<Machine> BoostStateMahine;

protected:
public:
  //FSetStateDelegate OnNewScenarioState;


};
