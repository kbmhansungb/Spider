// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameMode.h"
#include "MainMenuPlayerController.h"
#include "GameModule/GameModule.h"

#include "MainMenu.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	AMainMenuGameMode::PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	AMainMenuGameMode::DefaultPawnClass = AMainMenuCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<UMainMenu> BPMainMenuClass(TEXT("/Game/MainMenu/BP_MainMenu.BP_MainMenu_C"));
	if (BPMainMenuClass.Succeeded())
	{
		MainMenuClass = BPMainMenuClass.Class;
	}
	else
	{
		UE_LOG(LogMainMenu, Error, TEXT("Faild to load BP_MainMenu"));
	}
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainMenuClass))
	{
		MainMenuUI = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
	}
	else
	{
		UE_LOG(LogMainMenu, Error, TEXT("Faild to create MainMenu."));
		return;
	}

	if (IsValid(MainMenuUI))
	{
		MainMenuUI->AddToViewport();
	}
	else
	{
		UE_LOG(LogMainMenu, Error, TEXT("Faild to add to viewport."));
		return;
	}
}
