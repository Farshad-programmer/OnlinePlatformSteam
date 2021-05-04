// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MoveingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPLATFORMS_API AMoveingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMoveingPlatform();

virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere)
	float Speed = 20.f;

	UPROPERTY(EditAnywhere,Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();
private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers  = 1;
};
