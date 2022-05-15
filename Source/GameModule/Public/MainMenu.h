// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameModule.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UOverlay;
class UTextBlock;
class UButton;

/*
*	 A class to implement the main menu button, it is desireable to use it in the main menu.
*/
UCLASS(BlueprintType)
class GAMEMODULE_API UMainMenuButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuButton(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetDesireHeight();

	FORCEINLINE UOverlay* GetOverlay() { return Overlay; }
	FORCEINLINE UButton* GetButton() { return Button; }
	FORCEINLINE UTextBlock* GetTextBlock() { return TextBlock; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextHeightPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor BackgroundColor;

protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;

	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
};

/*
 * 
 */
UCLASS(BlueprintType)
class GAMEMODULE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintCallable)
	void OpenOption();

	UFUNCTION(BlueprintCallable)
	void ExitGame();

protected:
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* GameStartButton;

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* ExitButton;
};