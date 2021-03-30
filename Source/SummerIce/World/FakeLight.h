#pragma once

#include "GameFramework/Actor.h"
#include "FakeLight.generated.h"

class UProceduralMeshComponent;
class UMaterial;
class UMaterialInstanceDynamic;

UENUM(BlueprintType)
enum class EFakeLightChannel: uint8
{
  Default = 0,
  Collide = ECollisionChannel::ECC_GameTraceChannel1,
  Ignore = ECollisionChannel::ECC_GameTraceChannel2
};

UCLASS()
class SUMMERICE_API AFakeLight: public AActor
{
  GENERATED_BODY()

public:
  AFakeLight();
  void SetLightOpacity(const float & Opacity);
  void SetLightColor(const FLinearColor & Color);
  void SwitchLightState(const bool & State);

protected:
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;

private:
  void CreateProceduralMesh();
  void UpdateProceduralMesh();

public:
  UPROPERTY(Category = "Settings", EditAnywhere)
  bool bIsDynamic = true;

  UPROPERTY(Category = "Settings", EditAnywhere)
  uint32 PolygonNum = 50u;

  UPROPERTY(Category = "Settings", EditAnywhere)
  float Distance = 150.0f;

  UPROPERTY(Category = "Settings", EditAnywhere)
  float UpperFov = 360.0f;

  UPROPERTY(Category = "Settings", EditAnywhere)
  float LowerFov = 0.0f;

  UPROPERTY(Category = "Settings", EditAnywhere)
  UMaterial * Material = nullptr;

  UPROPERTY(Category = "Settings", EditAnywhere)
  FLinearColor LightColor;

  UPROPERTY(Category = "Settings", EditAnywhere)
  float LightOpacity;

  UPROPERTY(Category = "Settings", EditAnywhere)
  EFakeLightChannel CollisionChannel = EFakeLightChannel::Collide;

private:
  UWorld * _World;
  bool _bDrawMesh;

  // ProceduralMesh
  UPROPERTY(VisibleAnywhere)
  UProceduralMeshComponent * _ProcMesh;

  TArray<FVector> _Vertices;
  TArray<FVector2D> _UVs;

  UPROPERTY()
  UMaterialInstanceDynamic * _MaterialInst;
};
