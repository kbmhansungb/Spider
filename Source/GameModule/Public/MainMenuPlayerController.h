// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "MainMenuPlayerController.generated.h"

class UCameraComponent;
class UMainMenu;

/*
 *
 */
UCLASS()
class AMainMenuPlayerController final : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuPlayerController();

protected:
	virtual void BeginPlay() override;

};

UCLASS()
class AMainMenuCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	AMainMenuCharacter();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent;
};