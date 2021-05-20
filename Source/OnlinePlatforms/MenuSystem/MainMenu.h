// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	UMainMenu(const FObjectInitializer& ObjectIn);

	void SetServerList(TArray<FString>Servernames);

	void SetMenuInterface(IMenuInterface* SetedMenuInterFace);

	void Setup();
	void Teardown();

	// I bring this in public section because of BlueprintReadOnly
	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher1;
	
	UPROPERTY(meta = (BindWidget))
	class UWidget* Joinmenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;
	
protected:
	
	virtual bool Initialize() override;

private:
	
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmJoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	TSubclassOf<class UUserWidget>ServerRowClass;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();
	
	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void BackToMainMenu();

	UFUNCTION()
	void QuitGame();
	

	IMenuInterface* MenuInterface;
};
