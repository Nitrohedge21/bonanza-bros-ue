// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "MyPawnSensingComponent.generated.h"

/**
 * Custom Pawn Sensing Component supporting selectable collision trace channels
 * and multi-player sensing utilities.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BONANZABROSUE_API UMyPawnSensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()

public:
	UMyPawnSensingComponent();

	/** Custom Collision Channel used for Pawn Line of Sight checks */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Sensing")
	TEnumAsByte<ECollisionChannel> SightTraceChannel;

	/** Returns an array of all Player Pawns currently visible within SightRadius, FOV, and Line of Sight */
	UFUNCTION(BlueprintCallable, Category = "AI Sensing")
	TArray<APawn*> GetSensedPawns() const;

protected:
	// Overrides the sight evaluation (Distance + FOV + Custom Line Trace)
	virtual bool CouldSeePawn(const APawn* Other, bool bMaySkipChecks) const override;
};