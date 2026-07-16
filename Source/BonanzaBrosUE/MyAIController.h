// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class BONANZABROSUE_API AMyAIController : public AAIController
{
    GENERATED_BODY()

public:
    // Override the interface functions
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
    virtual FGenericTeamId GetGenericTeamId() const override;

    // Function to set team from Blueprints
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetTeamID(uint8 InTeamID);

private:
    FGenericTeamId TeamID;
};