// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEPLATFORMS_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup();
	void Teardown();
	
protected:
	
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UFUNCTION()
	void QuitMenu();

	UFUNCTION()
	void CancelGame();
	
	


};
