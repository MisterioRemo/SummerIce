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
      AInteractableObject * Item = Cast<AInteractableObject>(DialogSystem::FindItemInSpeaker());
      if (Item) OnAddItemDelegate.Broadcast(Item->GetObjectType());
      break;
    }
    //case EGameEventType::RemoveItem:
    //  OnRemoveItemDelegate.Broadcast(Actor);
    //  break;
    default:
      break;
  }
}