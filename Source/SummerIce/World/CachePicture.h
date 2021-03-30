#pragma once

#include "World/InteractableObject.h"
#include "CachePicture.generated.h"

UCLASS()
class SUMMERICE_API ACachePicture: public AInteractableObject
{
  GENERATED_BODY()

private:
  enum class EState
  {
    OnWall,
    OnFloor
  };

public:
  virtual void ChooseEvent() override;

protected:
  virtual void BeginPlay() override;

private:
  void MovePictureToFloor();

private:
  EState State;
};
