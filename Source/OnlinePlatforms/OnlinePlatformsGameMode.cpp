// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnlinePlatformsGameMode.h"
#include "OnlinePlatformsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOnlinePlatformsGameMode::AOnlinePlatformsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
