// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameModule.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UOverlay;
class UTextBlock;
class UButton;
class UWidgetAnimation;

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
	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//float GetDesireHeight();

	FORCEINLINE UOverlay* GetOverlay() { return Overlay; }
	FORCEINLINE UButton* GetButton() { return Button; }
	FORCEINLINE UTextBlock* GetTextBlock() { return TextBlock; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextSize;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float TextHeightPadding;

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
	virtual void NativeConstruct() override;

	UFUNCTION()
	bool IsBusy();

	UFUNCTION(BlueprintCallable)
	void Prepare();
	
	UFUNCTION(BlueprintCallable)
	void ExitGame();

	UFUNCTION(BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintCallable)
	void OnClicked_StartGame();

	// MainMenu Buttons
protected:
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* GameStartButton;

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* ExitButton;
	
	// Animations
protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FirstToMainMenuAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayFirstToMainMenuAnimation();

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ReadyToPlayAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayReadyToPlayAnimation();

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* MainMenuToPrepareAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayMainMenuToPrepareAnimation();

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* MainMenuToOptionAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayMainMenuToOptionAnimation();

	UFUNCTION(BlueprintCallable)
	void PlayOptionToMainMenuAnimation();

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* MainMenuToExitAnimation;

	UFUNCTION(BlueprintCallable)
	void PlayMainMenuToExitAnimation();
};