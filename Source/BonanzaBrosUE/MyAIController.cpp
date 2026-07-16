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
    // 1. Try to get the interface directly from the actor (e.g. if the Pawn implements it)
    const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);

    // 2. If the Pawn doesn't implement it, check if its Controller does
    if (!OtherTeamAgent)
    {
        if (const APawn* OtherPawn = Cast<const APawn>(&Other))
        {
            OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());
        }
    }

    // 3. If we successfully found a team agent, compare the IDs
    if (OtherTeamAgent)
    {
        if (OtherTeamAgent->GetGenericTeamId() == TeamID)
        {
            return ETeamAttitude::Friendly;
        }
    }

    return ETeamAttitude::Hostile;
}