#include "GameEvent.h"
#include "Util/DialogSystem.h"
#include "World/InteractableObject.h"

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


void UGameEvent::CallDialogEvent(EGameEventType & GEType)
{
  switch (GEType) {
    case EGameEventType::NoAction:
      break;
    case EGameEventType::TakeItem:
    {
      // lavinia takes item & item became hidden in the world (deleted?)
      if (auto Item = Cast<AInteractableObject>(DialogSystem::FindItemInSpeaker()))
        OnAddItemDelegate.Broadcast(Item->GetObjectType());
      break;
    }
    //case EGameEventType::RemoveItem:
    //  OnRemoveItemDelegate.Broadcast(Actor);
    //  break;
    case EGameEventType::Other:
    {
      if (auto Item = Cast<AInteractableObject>(DialogSystem::FindItemInSpeaker()))
        Item->ChooseEvent();
      break;
    }
    case EGameEventType::Pause:
    {

    }
    default:
      break;
  }
}