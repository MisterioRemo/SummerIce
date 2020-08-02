#pragma once
#include "CoreMinimal.h"
#include "GameEventType.h"
#include "Util/GameItem.h"
#include "GameEvent.generated.h"


// Класс UGameEvent - singleton, такакя реализация возникла потому,
// что крайне затруднительно создать static delegate с UPROPERTY

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddItemDelegate, EGameItem, Item);


UCLASS()
class SUMMERICE_API UGameEvent : public UObject
{
	GENERATED_BODY()
	
private:
  UGameEvent();

protected:
public:
  UFUNCTION()
  static UGameEvent * Instance();

  void CallDialogEvent(EGameEventType & GEType);

public:
  UPROPERTY(BlueprintAssignable, Category = "Item Action Delegate")
  FAddItemDelegate OnAddItemDelegate;

  UPROPERTY(BlueprintAssignable, Category = "Item Action Delegate")
  FAddItemDelegate OnRemoveItemDelegate;
};
