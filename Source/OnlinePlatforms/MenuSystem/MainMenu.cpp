// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextBlock.h"
#include "ServerRow.h"


UMainMenu::UMainMenu(const FObjectInitializer& ObjectIn) :Super(ObjectIn)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (ServerRowBPClass.Class)
	{
		ServerRowClass = ServerRowBPClass.Class;
	}
}

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


void UMainMenu::SetServerList(TArray<FString>Servernames)
{
	ServerList->ClearChildren();

	for (const FString& ServerName : Servernames )
	{
		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRowClass);
		if (Row)
		{
			Row->Servername->SetText(FText::FromString(ServerName));
			ServerList->AddChild(Row);
		}
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		/*if (IPAddressField)
		{
			const FString Address = IPAddressField->GetText().ToString();
			MenuInterface->Join(Address);
		}*/
		MenuInterface->Join("");
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher1 && Joinmenu)
	{
		MenuSwitcher1->SetActiveWidget(Joinmenu);
	}
	if (MenuInterface)
	{
		MenuInterface->RefreshServerList();
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




