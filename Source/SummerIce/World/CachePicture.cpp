#include "CachePicture.h"
#include "PaperFlipbookComponent.h"

void ACachePicture::BeginPlay()
{
  Super::BeginPlay();

  State = EState::OnWall;
}

void ACachePicture::ChooseEvent()
{
  switch (State) {
    case EState::OnWall:
      MovePictureToFloor();
      break;
    case EState::OnFloor:
      break;
    default:
      break;
  }
}

void ACachePicture::MovePictureToFloor()
{
  _BodyFlipbookComponent->SetRelativeLocation(FVector(5.0f, 0.0f, -19.0f));
}