// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlinePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UOnlinePlatformsGameInstance::UOnlinePlatformsGameInstance(const FObjectInitializer& ObjectIn)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuBPClass.Class)
	{
		MenuClass = MenuBPClass.Class;
	}
	
}

void UOnlinePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp,Warning,TEXT("Found Class %s"),*MenuClass->GetName());
}

void UOnlinePlatformsGameInstance::LoadMenu()
{
	if (MenuClass)
	{
		Menu = CreateWidget<UMainMenu>(this,MenuClass);
		if (Menu)
		{
			Menu->SetMenuInterface(this);
			Menu->Setup();
		}
	}
}

// Create Host part to game , so first player can create a host 
void UOnlinePlatformsGameInstance::Host()
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}
	GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Red,TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

// Create Join part to game , so other players can join to host 
void UOnlinePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}
	GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Red,FString::Printf(TEXT("Joing %s"),*Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
	}
}
