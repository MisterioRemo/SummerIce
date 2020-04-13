#include "MyPawnMovementComponent.h"
#include "GameFramework/Pawn.h"

//#include "DrawDebugHelpers.h"
#include "Engine/World.h"

UMyPawnMovementComponent::UMyPawnMovementComponent()
{
	WalkSpeed = 20.0f;
	RunSpeed = 30.0f;
	GravityScale = 10.0f;
	Mass = 10.0f;
}

void UMyPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	Sanitize();
	FVector Gravity = GetGravityDirection();
	FVector PropReaction = GetPropReaction();
	FVector AntiFriction = -1 * GetFriction(PropReaction, Gravity);
	FVector DesiredMovementThisFrame = (_MovementInput * WalkSpeed + Gravity + PropReaction + AntiFriction) * DeltaTime;

	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		if (Hit.IsValidBlockingHit()) {
			//DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(),
			//			  PawnOwner->GetActorLocation() + (_MovementInput * WalkSpeed + Gravity + PropReaction + AntiFriction),
			//			  FColor::Black, false, 1, 0, 1);
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}		
	}
};

void UMyPawnMovementComponent::Sanitize()
{
	_MovementInput = ConsumeInputVector().GetClampedToMaxSize(1.0f).GetSafeNormal();
}

FVector UMyPawnMovementComponent::GetGravityDirection() const
{
	//DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(),
	//			  PawnOwner->GetActorLocation() + FVector(0.0f, 0.0f, -1.0f) * GravityScale,
	//			  FColor::Red, false, 1, 0, 1);
	return FVector(0.0f, 0.0f, -1.0f) * GravityScale * Mass;
}

FVector UMyPawnMovementComponent::GetPropReaction() const
{
	FHitResult OutHit;
	FVector Start = PawnOwner->GetActorLocation();
	FVector End = Start + FVector(0.0f, 0.0f, -15.0f);	// 10.0 radius collision body
	FCollisionQueryParams CollisionParams;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams)) {
		//DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(),
		//			  PawnOwner->GetActorLocation() + OutHit.ImpactNormal * GravityScale,
		//			  FColor::Green, false, 1, 0, 1);
		return OutHit.ImpactNormal * GravityScale;
	}	
	return FVector::ZeroVector;
}

FVector UMyPawnMovementComponent::GetFriction(const FVector & PropReaction, const FVector & Gravity) const
{
	if (!PropReaction.IsNearlyZero()) {
		//DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(),
		//			  PawnOwner->GetActorLocation() + Gravity + PropReaction,
		//			  FColor::Cyan, false, 1, 0, 1);
		return Gravity + PropReaction;
	}
	return FVector::ZeroVector;
}