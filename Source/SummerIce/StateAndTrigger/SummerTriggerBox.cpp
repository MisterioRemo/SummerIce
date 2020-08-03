#include "SummerTriggerBox.h"
#include "GameEvent.h"

ASummerTriggerBox::ASummerTriggerBox()
{
  PrimaryActorTick.bCanEverTick = false;

  OnActorBeginOverlap.AddDynamic(this, &ASummerTriggerBox::OnOverlapBegin);
  OnActorEndOverlap.AddDynamic(this, &ASummerTriggerBox::OnOverlapEnd);
}

void ASummerTriggerBox::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
  if (EventTiming == EActionTiming::OverlapBegin && OtherActor && OtherActor != this) {
    // UE_LOG(LogTemp, Warning, TEXT("begin\t over = %s,\t other=%s"), *OverlappedActor->GetName(), *OtherActor->GetName());
    ChooseEvent();
  }
}

void ASummerTriggerBox::OnOverlapEnd(AActor * OverlappedActor, AActor * OtherActor)
{
  if (OtherActor && OtherActor != this) {
  }

  if (EventTiming == EActionTiming::OverlapEnd && OtherActor && OtherActor != this) {
    // UE_LOG(LogTemp, Warning, TEXT("end\t over = %s,\t other=%s"), *OverlappedActor->GetName(), *OtherActor->GetName());
    ChooseEvent();
  }
}

void ASummerTriggerBox::ChooseEvent()
{
  switch (EventType) {
    case EGameEventType::NoAction:
      break;
    case EGameEventType::TakeItem:
      UGameEvent::Instance()->OnAddItemDelegate.Broadcast(ItemType);
      break;
    case EGameEventType::RemoveItem:
      UGameEvent::Instance()->OnRemoveItemDelegate.Broadcast(ItemType);
      break;
    default:
      break;
  }
}