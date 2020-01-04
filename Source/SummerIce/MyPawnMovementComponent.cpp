#include "MyPawnMovementComponent.h"
#include "GameFramework/Pawn.h"

UMyPawnMovementComponent::UMyPawnMovementComponent()
{
	WalkSpeed = 20.0f;
	RunSpeed = 30.0f;
}

void UMyPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}
		
	Sanitize();
	FVector DesiredMovementThisFrame = _MovementInput * WalkSpeed * DeltaTime;

	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		//FVector Pos = GetPawnOwner()->GetActorLocation();

		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if (Hit.IsValidBlockingHit()) {
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}		
	}
};

void UMyPawnMovementComponent::Sanitize()
{
	_MovementInput = ConsumeInputVector().GetClampedToMaxSize(1.0f).GetSafeNormal();
}

void UMyPawnMovementComponent::Interact(bool bPressed)
{
	_bIinteract = bPressed;
}