#include "FakeLight.h"
#include "UObject/ConstructorHelpers.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

//#include "DrawDebugHelpers.h"

AFakeLight::AFakeLight()
{
  PrimaryActorTick.bCanEverTick = true;
  
  _ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
  _ProcMesh->bUseAsyncCooking = true;
  SetRootComponent(_ProcMesh);

  ConstructorHelpers::FObjectFinder<UMaterial> Finder
  (TEXT("Material'/Game/Material/MT_FakeLight.MT_FakeLight'"));
  if (Finder.Succeeded()) _MaterialInst = UMaterialInstanceDynamic::Create(Finder.Object, NULL);
}

void AFakeLight::BeginPlay()
{
	Super::BeginPlay();

  if (Material)
    _MaterialInst = UMaterialInstanceDynamic::Create(Material, NULL);

  SetLightColor(LightColor);
  SetLightOpacity(LightOpacity);
  CreateProceduralMesh();
  if (!bIsDynamic)
    UpdateProceduralMesh();

  _World = GetWorld();
}

void AFakeLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  if (bIsDynamic && _bDrawMesh) UpdateProceduralMesh();  
}


void AFakeLight::CreateProceduralMesh()
{
  _Vertices.Init(FVector(0.0f), PolygonNum + 1);
  _UVs.Init(FVector2D(0.0f), PolygonNum + 1);
  TArray<int32> _Triangles;
  for (int32 i = 1; i < static_cast<int32>(PolygonNum); ++i)
    _Triangles.Append({ 0, i, i + 1 });
  _Triangles.Append({ 0, static_cast<int32>(PolygonNum), 1 }); // last section, i dunno why

  _ProcMesh->SetMaterial(0, _MaterialInst);
  _ProcMesh->CreateMeshSection(0, _Vertices, _Triangles, FOccluderVertexArray(), _UVs,
                               TArray<FColor>(),TArray<FProcMeshTangent>(), false);
}

void AFakeLight::UpdateProceduralMesh()
{
  _Vertices.Reset();
  _UVs.Reset();
  _Vertices.Emplace(FVector(0.0f));
  _UVs.Emplace(FVector2D(0.0f));

  FHitResult OutHit;
  const FVector ActorLocation = GetActorLocation();
  const FRotator ActorRotation = GetActorRotation();
  const FRotator AngleRotation{ (UpperFov - LowerFov) / PolygonNum, 0.0f, 0.0f };
  const FVector Start{ 0.0f };
  FVector End = (ActorRotation - FRotator{ (UpperFov - LowerFov) / 2, 0.0f, 0.0f }).RotateVector({ Distance, 0.0f, 0.0f });

  for (uint32 i = 0; i < PolygonNum; ++i) {
    if (_World->LineTraceSingleByChannel(OutHit, ActorLocation + Start, ActorLocation + End,
                                         static_cast<ECollisionChannel>(CollisionChannel))) {
      //DrawDebugLine(_World, ActorLocation + Start, OutHit.Location, FColor::Blue, false, 0.1f);
      const FVector HitLocation = ActorRotation.GetInverse().RotateVector(OutHit.Location - ActorLocation);
      _Vertices.Emplace(HitLocation);
      _UVs.Emplace(FVector2D(HitLocation.Size() / Distance, 0.0f));
    }
    else {
      //DrawDebugLine(_World, ActorLocation + Start, OutHit.TraceEnd, FColor::Red, false, 0.1f);
      _Vertices.Emplace(ActorRotation.GetInverse().RotateVector(OutHit.TraceEnd - ActorLocation));
      _UVs.Emplace(FVector2D(1.0f, 0.0f));
    }
    End = AngleRotation.RotateVector(End);
  }

  _ProcMesh->UpdateMeshSection(0, _Vertices, FOccluderVertexArray(), _UVs, TArray<FColor>(), TArray<FProcMeshTangent>());
}

void AFakeLight::SetLightOpacity(const float & Opacity)
{
  _MaterialInst->SetScalarParameterValue(TEXT("LightOpacity"), Opacity);
}

void AFakeLight::SetLightColor(const FLinearColor & Color)
{
  _MaterialInst->SetVectorParameterValue(TEXT("LightColor"), Color);
}

void AFakeLight::SwitchLightState(const bool & State)
{
  _bDrawMesh = State;
  if (!_bDrawMesh) _ProcMesh->ClearAllMeshSections();
  else CreateProceduralMesh();
}