#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "MyPawnMovementComponent.generated.h"

UCLASS()
class SUMMERICE_API UMyPawnMovementComponent: public UPawnMovementComponent
{
  GENERATED_BODY()

private:
  void Sanitize();
  FVector GetGravityDirection() const;
  FVector GetPropReaction() const;
  FVector GetFriction(const FVector & PropReaction, const FVector & Gravity) const;

protected:
  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Parametrs", meta = (ClampMin = "0.0"))
  float WalkSpeed;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Parametrs", meta = (ClampMin = "0.0"))
  float RunSpeed;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Parametrs", meta = (ClampMin = "0.0"))
  float GravityScale;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Parametrs", meta = (ClampMin = "0.0"))
  float Mass;

public:
  UMyPawnMovementComponent();
  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
  FVector _MovementInput;

public:
};
