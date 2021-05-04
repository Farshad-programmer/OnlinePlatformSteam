// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveingPlatform.h"

AMoveingPlatform::AMoveingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMoveingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}


void AMoveingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
			float JourneLenght = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneTraveled = (Location - GlobalStartLocation).Size();
			if (JourneTraveled >= JourneLenght)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}	
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Speed * DeltaSeconds * Direction;
			SetActorLocation(Location);
		}
	}

}


void AMoveingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMoveingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}