#pragma once
#pragma warning(disable: 4668)

#include "CoreMinimal.h"

#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>

#include "ScenarioStateMachine.generated.h"

namespace sc = boost::statechart;

// We are declaring all types as structs only to avoid having to
// type public. If you don't mind doing so, you can just as well
// use class.

// We need to forward-declare the initial state because it can
// only be defined at a point where the state machine is
// defined.
struct Greeting;

// Boost.Statechart makes heavy use of the curiously recurring
// template pattern. The deriving class must always be passed as
// the first parameter to all base class templates.
//
// The state machine must be informed which state it has to
// enter when the machine is initiated. That's why Greeting is
// passed as the second template parameter.
struct Machine: sc::state_machine< Machine, Greeting > {};

// For each state we need to define which state machine it
// belongs to and where it is located in the statechart. Both is
// specified with Context argument that is passed to
// simple_state<>. For a flat state machine as we have it here,
// the context is always the state machine. Consequently,
// Machine must be passed as the second template parameter to
// Greeting's base (the Context parameter is explained in more
// detail in the next example).
struct Greeting: sc::simple_state< Greeting, Machine >
{
  // Whenever the state machine enters a state, it creates an
  // object of the corresponding state class. The object is then
  // kept alive as long as the machine remains in the state.
  // Finally, the object is destroyed when the state machine
  // exits the state. Therefore, a state entry action can be
  // defined by adding a constructor and a state exit action can
  // be defined by adding a destructor.
  Greeting() { } // entry
  ~Greeting() {  } // exit
};
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetStateDelegate, ScenarioState, State);

UCLASS()
class SUMMERICE_API UScenarioStateMachine : public UObject
{
	GENERATED_BODY()

private:
  UScenarioStateMachine();

protected:
public:
  UScenarioStateMachine * Instance();

private:

protected:
public:
  //FSetStateDelegate OnNewScenarioState;
  
	
};
