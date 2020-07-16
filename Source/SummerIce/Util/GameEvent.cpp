#include "GameEvent.h"

UGameEvent::UGameEvent() : Super()
{ }

UGameEvent* UGameEvent::Instance()
{
  static UGameEvent * Inst = nullptr;
  if (!Inst) {
    Inst = NewObject<UGameEvent>();
    Inst->AddToRoot();
  }
  return Inst;
}
