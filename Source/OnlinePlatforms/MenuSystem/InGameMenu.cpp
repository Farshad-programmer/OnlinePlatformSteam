// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (QuitButton == nullptr)
	{
		return false;
	}
	QuitButton->OnClicked.AddDynamic(this,&UInGameMenu::QuitMenu);

	if (CancelButton == nullptr)
	{
		return false;
	}
	CancelButton->OnClicked.AddDynamic(this,&UInGameMenu::CancelGame);


	return true;
}

void UInGameMenu::Setup()
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

void UInGameMenu::Teardown()
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





void UInGameMenu::QuitMenu()
{
	GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,TEXT("Quit"));
	UGameplayStatics::OpenLevel(GetWorld(),FName("Menu"));
}

void UInGameMenu::CancelGame()
{
	GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,TEXT("Cancel"));
	Teardown();
}


