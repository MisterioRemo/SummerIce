#pragma once
#pragma warning(push, 1)
#pragma warning(disable: 4668) // hide warning and error when include boost
#pragma warning(disable: 4265) // hide warning class has virtual functions, but destructor is not virtual

#include "SummerIce.h"
#include "Engine/World.h"
#include "ScenarioStateMachine.h"

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

class UScenarioStateMachine;

// State
struct StateHouseSurvey;
struct StateLeaveHouse;
struct StateMeetFransina;
struct StateEnterForest;
struct StateFindElizabeth;
struct StatePoliceArrived;
struct StateLeaveForest;
struct StateMeetHelen;
struct StateEnterPharmacy;
struct StateEnterCafe;
struct StateEnterCinema;
struct StateLeaveBuilding;
struct StateTakeHomeFrancina;
struct StateTakeHomeHelen;
struct StateMeetSergeant;
struct StateEnterDarkForest;
struct StateLeaveDarkForest;
struct StateEnterHouse;

struct StateLavAliveHeAlive;
struct StateLavAliveHeDie;
struct StateLavDieHeAlive;
struct StateLavDieHeDie;

struct StateHeRunAway;
struct StateHeIsCaught;


// Mashine
struct Machine: sc::state_machine<Machine, StateHouseSurvey>
{
  UScenarioStateMachine * _Parent;

  void set_parent(UScenarioStateMachine * Parent)
  {
    _Parent = Parent;
  }
};

// Event
struct EventMoveToNextState: sc::event<EventMoveToNextState> {};
struct EventDieLikeAMan: sc::event<EventDieLikeAMan> {};
struct EventWindowIsOurSalvation: sc::event<EventWindowIsOurSalvation> {};
struct EventHideInDark: sc::event<EventHideInDark> {};
struct EventScissorsIsACheat: sc::event<EventScissorsIsACheat> {};
struct EventShootBaby: sc::event<EventShootBaby> {};
struct EventFryHim: sc::event<EventFryHim> {};
struct EventFryHimAndYourself: sc::event<EventFryHimAndYourself> {};
struct EventIAmAGhost: sc::event<EventIAmAGhost> {};
struct EventIWasTheGhost: sc::event<EventIWasTheGhost> {};
struct EventMakeADeal: sc::event<EventMakeADeal> {};


struct StateHouseSurvey: sc::simple_state<StateHouseSurvey, Machine>
{
  typedef sc::custom_reaction<EventMoveToNextState> reactions;

  sc::result react(const EventMoveToNextState &event)
  {
    UE_LOG(LogSummer, Warning, TEXT("trans from StateHouseSurvey to StateLeaveHouse or StateMeetFransina. Check timer for explorarion street."));
    float Time = 5.0;// context<Machine>()._Parent->GetWorld()->GetTimeSeconds();
    return (Time < 5.0f * 60.0f) ? transit<StateLeaveHouse>() : transit<StateMeetFransina>();
  }
};

struct StateLeaveHouse: sc::simple_state<StateLeaveHouse, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateMeetFransina> reactions;
};

struct StateMeetFransina: sc::simple_state<StateMeetFransina, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateEnterForest> reactions;
};

struct StateEnterForest: sc::simple_state<StateEnterForest, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateFindElizabeth> reactions;
};

struct StateFindElizabeth: sc::simple_state<StateFindElizabeth, Machine>
{
  typedef sc::transition<EventMoveToNextState, StatePoliceArrived> reactions;
};

struct StatePoliceArrived: sc::simple_state<StatePoliceArrived, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateLeaveForest> reactions;
};

struct StateLeaveForest: sc::simple_state<StateLeaveForest, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateMeetHelen> reactions;
};

struct StateMeetHelen: sc::simple_state<StateMeetHelen, Machine>
{
  typedef mpl::list <
    sc::transition<EventMoveToNextState, StateEnterPharmacy>,
    sc::transition<EventMoveToNextState, StateEnterCafe>,
    sc::transition<EventMoveToNextState, StateEnterCinema>
  > reactions;
};

struct StateEnterPharmacy: sc::simple_state<StateEnterPharmacy, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateLeaveBuilding> reactions;
};

struct StateEnterCafe: sc::simple_state<StateEnterCafe, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateLeaveBuilding> reactions;
};

struct StateEnterCinema: sc::simple_state<StateEnterCinema, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateLeaveBuilding> reactions;
};

struct StateLeaveBuilding: sc::simple_state<StateLeaveBuilding, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateTakeHomeFrancina> reactions;
};

struct StateTakeHomeFrancina: sc::simple_state<StateTakeHomeFrancina, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateTakeHomeHelen> reactions;
};

struct StateTakeHomeHelen: sc::simple_state<StateTakeHomeHelen, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateMeetSergeant> reactions;
};

struct StateMeetSergeant: sc::simple_state<StateMeetSergeant, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateEnterDarkForest> reactions;
};

struct StateEnterDarkForest: sc::simple_state<StateEnterDarkForest, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateLeaveDarkForest> reactions;
};

struct StateLeaveDarkForest: sc::simple_state<StateLeaveDarkForest, Machine>
{
  typedef sc::transition<EventMoveToNextState, StateEnterHouse> reactions;
};

struct StateEnterHouse: sc::simple_state<StateEnterHouse, Machine>
{
  typedef mpl::list <
    sc::transition<EventDieLikeAMan, StateLavDieHeAlive>,
    sc::transition<EventWindowIsOurSalvation, StateLavAliveHeAlive>,
    sc::transition<EventHideInDark, StateLavAliveHeAlive>,
    sc::transition<EventScissorsIsACheat, StateLavAliveHeDie>,
    sc::transition<EventShootBaby, StateLavAliveHeDie>,
    sc::transition<EventFryHim, StateLavAliveHeDie>,
    sc::transition<EventFryHimAndYourself, StateLavDieHeDie>,
    sc::transition<EventIAmAGhost, StateLavDieHeAlive>,
    sc::transition<EventIWasTheGhost, StateLavAliveHeAlive>,
    sc::transition<EventMakeADeal, StateLavAliveHeDie>
  > reactions;
};

struct StateLavAliveHeAlive: sc::simple_state<StateLavAliveHeAlive, Machine>
{
  typedef mpl::list <
    sc::transition<EventDieLikeAMan, StateHeRunAway>,
    sc::transition<EventWindowIsOurSalvation, StateHeIsCaught>
  > reactions;
};

struct StateLavAliveHeDie: sc::simple_state<StateLavAliveHeDie, Machine> {};

struct StateLavDieHeAlive: sc::simple_state<StateLavDieHeAlive, Machine> {};

struct StateLavDieHeDie: sc::simple_state<StateLavDieHeDie, Machine> {};

struct StateHeRunAway: sc::simple_state<StateHeRunAway, Machine> {};

struct StateHeIsCaught: sc::simple_state<StateHeIsCaught, Machine> {};

#pragma warning(pop)
