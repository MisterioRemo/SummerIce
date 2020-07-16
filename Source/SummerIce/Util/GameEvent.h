#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameEvent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddItemDelegate, AActor*, Item);

// Класс UGameEvent - singleton, такакя реализация возникла потому,
// что крайне затруднительно создать static delegate с UPROPERTY

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

public:
  UPROPERTY(BlueprintAssignable, Category = "Test")
  FAddItemDelegate OnAddItemDelegate;
};
