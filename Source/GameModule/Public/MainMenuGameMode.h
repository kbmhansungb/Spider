// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

class UMainMenu;

/*
 * 
 */
UCLASS(BlueprintType)
class AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameMode();

protected:
	virtual void BeginPlay() override;

#pragma region MainMenu Widget
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMainMenu> MainMenuClass;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UMainMenu* MainMenuUI;

#pragma endregion
};
