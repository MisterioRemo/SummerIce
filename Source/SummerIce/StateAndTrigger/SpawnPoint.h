#pragma once

#include "GameFramework/Actor.h"
#include "GameEventType.h"
#include "SpawnPoint.generated.h"

class UArrowComponent;
class UBillboardComponent;

UCLASS()
class SUMMERICE_API ASpawnPoint: public AActor
{
  GENERATED_BODY()

public:
  ASpawnPoint(const FObjectInitializer& ObjectInitializer);

  FVector GetPointLocation() const;
  FVector GetPointDiretion() const;
  ETeleportLocation GetTeleportLocationName() const;

private:
  UPROPERTY()
  UArrowComponent * _Direction;

  UPROPERTY(EditAnywhere, Category = "Settings")
  ETeleportLocation _LocationName;

#if WITH_EDITORONLY_DATA
  // Billboard used to see the spawn point in the editor 
  UPROPERTY()
  UBillboardComponent * _SpriteComponent;
#endif

};
