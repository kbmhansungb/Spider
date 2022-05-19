// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"
#include "GameModule/GameModule.h"

#include "MainMenu.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	APlayerController::bShowMouseCursor = true;
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

AMainMenuCharacter::AMainMenuCharacter()
{
}

void AMainMenuCharacter::BeginPlay()
{
	Super::BeginPlay();
}
