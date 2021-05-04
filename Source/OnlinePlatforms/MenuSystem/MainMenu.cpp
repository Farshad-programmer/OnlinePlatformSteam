// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (HostButton == nullptr)
	{
		return false;
	}
	HostButton->OnClicked.AddDynamic(this,&UMainMenu::HostServer);

	if (JoinButton == nullptr)
	{
		return false;
	}
	JoinButton->OnClicked.AddDynamic(this,&UMainMenu::OpenJoinMenu);

	if (CancelButton == nullptr)
	{
		return false;
	}
	CancelButton->OnClicked.AddDynamic(this,&UMainMenu::BackToMainMenu);

	if (ConfirmJoinButton == nullptr)
	{
		return false;
	}
	ConfirmJoinButton->OnClicked.AddDynamic(this,&UMainMenu::JoinServer);

	if (QuitGameButton == nullptr)
	{
		return false;
	}
	QuitGameButton->OnClicked.AddDynamic(this,&UMainMenu::QuitGame);
	
	return true;
	
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		if (IPAddressField)
		{
			const FString Address = IPAddressField->GetText().ToString();
			MenuInterface->Join(Address);
		}
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher1 && Joinmenu)
	{
		MenuSwitcher1->SetActiveWidget(Joinmenu);
	}
	
}

void UMainMenu::BackToMainMenu()
{
	if (MenuSwitcher1 && MainMenu)
	{
		MenuSwitcher1->SetActiveWidget(MainMenu);
	}
}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (World == nullptr){return;}
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController)
	{
		// UKismetSystemLibrary::QuitGame(GetWorld(),PlayerController,EQuitPreference::Quit,false);
		PlayerController->ConsoleCommand("quit");
	}
	
}

void UMainMenu::SetMenuInterface(IMenuInterface* SetedMenuInterFace)
{
	this->MenuInterface = SetedMenuInterFace;
}

void UMainMenu::Setup()
{
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (World == nullptr){return;}
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeUIOnly InputModeData;
		// InputModeData.SetWidgetToFocus(this->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = true;
	}
}

void UMainMenu::Teardown()
{
	this->RemoveFromViewport();
	UWorld* World = GetWorld();
	if (World == nullptr){return;}
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeGameOnly InputModeData;
		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = false;
	}
}