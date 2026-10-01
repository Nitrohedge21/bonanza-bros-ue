// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnSensingComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"

UMyPawnSensingComponent::UMyPawnSensingComponent()
{
	// Default to standard Visibility, editable in Blueprint
	SightTraceChannel = ECC_Visibility;
}

bool UMyPawnSensingComponent::CouldSeePawn(const APawn* Other, bool bMaySkipChecks) const
{
	if (!Other)
	{
		return false;
	}

	const AActor* Owner = GetOwner();
	if (!Owner)
	{
		return false;
	}

	FVector const OtherLoc = Other->GetActorLocation();
	FVector const SensorLoc = GetSensorLocation();
	FVector const SelfToOther = OtherLoc - SensorLoc;

	// 1. Max sight distance check
	FVector::FReal const SelfToOtherDistSquared = SelfToOther.SizeSquared();
	if (SelfToOtherDistSquared > FMath::Square(SightRadius))
	{
		return false;
	}

	// 2. Random check skip optimization
	if (bMaySkipChecks && (FMath::Square(FMath::FRand()) * SelfToOtherDistSquared > FMath::Square(0.4f * SightRadius)))
	{
		return false;
	}

	// 3. Field of View check
	FVector const SelfToOtherDir = SelfToOther.GetSafeNormal();
	FVector const MyFacingDir = GetSensorRotation().Vector();

	if ((SelfToOtherDir | MyFacingDir) < PeripheralVisionCosine)
	{
		return false;
	}

	// 4. Custom Line Trace using selected SightTraceChannel
	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	FHitResult HitResult;
	FCollisionQueryParams QueryParams(FName(TEXT("PawnSensingLineTrace")), true, Owner);
	QueryParams.AddIgnoredActor(Owner);

	bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		SensorLoc,
		OtherLoc,
		SightTraceChannel,
		QueryParams
	);

	// Line of sight is clear if no obstacle blocked the channel or if we hit the target pawn directly
	if (!bHit || HitResult.GetActor() == Other)
	{
		return true;
	}

	return false;
}

TArray<APawn*> UMyPawnSensingComponent::GetSensedPawns() const
{
	TArray<APawn*> VisiblePawns;

	UWorld* World = GetWorld();
	if (!World)
	{
		return VisiblePawns;
	}

	// Iterate through all Player Controllers / Pawns in the world
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			APawn* TargetPawn = PC->GetPawn();
			// Evaluate against our custom CouldSeePawn check
			if (TargetPawn && CouldSeePawn(TargetPawn, false))
			{
				VisiblePawns.AddUnique(TargetPawn);
			}
		}
	}

	return VisiblePawns;
}