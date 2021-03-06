// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlinePlatformsGameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"


#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"


const static FName SESSION_NAME = TEXT("My Session game");

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
	// UE_LOG(LogTemp,Warning,TEXT("Found Class %s"),*MenuClass->GetName());
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem)
	{
		UE_LOG(LogTemp,Warning,TEXT("Found SubSystem: %s"),*SubSystem->GetSubsystemName().ToString());
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UOnlinePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UOnlinePlatformsGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UOnlinePlatformsGameInstance::OnFindSessionsComplete);

			
			
		}
	}
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
	if (SessionInterface.IsValid())
	{
		auto ExisitingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExisitingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		} 
		else
		{
			CreateSesion();
		}
	}
}

void UOnlinePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create session!"));
		return;
	}

	if (Menu != nullptr)
	{
		Menu->Teardown();
	}
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}


void UOnlinePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSesion();
	}
}


void UOnlinePlatformsGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		UE_LOG(LogTemp, Warning, TEXT("Starting to Find Session!!"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}


void UOnlinePlatformsGameInstance::OnFindSessionsComplete(bool Success)
{
	if (Success && SessionSearch.IsValid() && Menu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finishing Find Session!!"));

		TArray<FString>Servernames;

		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session name:%s"),*SearchResult.GetSessionIdStr());
			Servernames.Add(SearchResult.GetSessionIdStr());
		}

		Menu->SetServerList(Servernames);
	}
	
}

void UOnlinePlatformsGameInstance::CreateSesion()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSetting;
		SessionSetting.bIsLANMatch = true;
		SessionSetting.NumPublicConnections = 2;
		SessionSetting.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSetting);
	}
}

// Create Join part to game , so other players can join to host 
void UOnlinePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr)
	{
		/*Menu->Teardown();*/
		Menu->SetServerList({ "test1" ,"test2" });
	}
	/*GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, FString::Printf(TEXT("Joing %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}*/
}




