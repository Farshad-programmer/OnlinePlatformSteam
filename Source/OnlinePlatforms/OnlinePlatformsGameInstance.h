// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

private:
	TSubclassOf<class UUserWidget>MenuClass;

	class UMainMenu* Menu;
	
};
