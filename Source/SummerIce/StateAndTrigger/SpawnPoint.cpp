#include "SpawnPoint.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "UObject/ConstructorHelpers.h"

ASpawnPoint::ASpawnPoint(const FObjectInitializer& ObjectInitializer)
  :Super(ObjectInitializer)
{
  PrimaryActorTick.bCanEverTick = false;

  _SpriteComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
  SetRootComponent(_SpriteComponent);
  _Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
  _Direction->SetEditorScale(0.4);
  _Direction->SetupAttachment(RootComponent);

  ConstructorHelpers::FObjectFinder<UTexture2D> Finder
  (TEXT("Texture2D'/Game/Sprite/Texture/Helper/SpawnPoint.SpawnPoint'"));
  if (Finder.Succeeded()) _SpriteComponent->SetSprite(Finder.Object);

  _LocationName = ETeleportLocation::None;
}

FVector ASpawnPoint::GetPointLocation() const
{
  FVector Location = GetActorLocation();
  Location.SetComponentForAxis(EAxis::Y, 0.0f);
  return Location;
}

FVector ASpawnPoint::GetPointDiretion() const
{
  return _Direction->GetForwardVector();
}

ETeleportLocation ASpawnPoint::GetTeleportLocationName() const
{
  return _LocationName;
}