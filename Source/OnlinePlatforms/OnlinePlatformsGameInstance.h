// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlinePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPLATFORMS_API UOnlinePlatformsGameInstance : public UGameInstance,public IMenuInterface
{
	GENERATED_BODY()
public:
	
	UOnlinePlatformsGameInstance(const FObjectInitializer & ObjectIn);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

	void RefreshServerList()override;

private:
	TSubclassOf<class UUserWidget>MenuClass;


	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;


	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);

	void CreateSesion();

};
