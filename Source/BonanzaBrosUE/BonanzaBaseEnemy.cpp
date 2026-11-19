// Fill out your copyright notice in the Description page of Project Settings.


#include "BonanzaBaseEnemy.h"

// Sets default values
ABonanzaBaseEnemy::ABonanzaBaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABonanzaBaseEnemy::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	// The socket name needs to be the same as it is on the attached mesh
	OutLocation = GetMesh()->GetSocketLocation("EyeSocket");

	OutRotation = GetMesh()->GetSocketRotation("EyeSocket");
}

// Called when the game starts or when spawned
void ABonanzaBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABonanzaBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABonanzaBaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

