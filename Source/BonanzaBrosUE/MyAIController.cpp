// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

void AMyAIController::SetTeamID(uint8 InTeamID)
{
    TeamID = FGenericTeamId(InTeamID);
}

FGenericTeamId AMyAIController::GetGenericTeamId() const
{
    return TeamID;
}

ETeamAttitude::Type AMyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
    if (OtherTeamAgent)
    {
        // If IDs match, treat as friendly
        if (OtherTeamAgent->GetGenericTeamId() == TeamID)
        {
            return ETeamAttitude::Friendly;
        }
    }
    return ETeamAttitude::Hostile;
}