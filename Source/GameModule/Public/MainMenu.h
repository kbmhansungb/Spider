// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UOverlay;
class UTextBlock;
class UButton;
class UWidgetAnimation;



/*
*	 A class to implement the main menu button, 
*	it is desirable to use it in the main menu.
*/
UCLASS()
class GAMEMODULE_API UMainMenuButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuButton(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;
public:
	FORCEINLINE UOverlay* GetOverlay() { return Overlay; }
	FORCEINLINE UButton* GetButton() { return Button; }
	FORCEINLINE UTextBlock* GetTextBlock() { return TextBlock; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextSize;

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
UCLASS()
class GAMEMODULE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	bool IsBusy();

private:
	UWidgetAnimation* LastAnimation;
protected:
	void PlayAnimation(UWidgetAnimation* NewAnimation);

#pragma region First
	
private:
	void InitFirst();
protected:
	UFUNCTION(BlueprintCallable)
	void OpenFirst();

public:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpenFirstAnimation;

#pragma endregion

#pragma region MainMenu

private:
	void InitMainMenu();
protected:
	UFUNCTION(BlueprintCallable)
	void OpenMainMenu();

public:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpenMainMenuAnimation;
	

protected:
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* GameStartButton;
	
	UFUNCTION(BlueprintCallable)
	void OnClicked_GameStartButton();

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* OptionButton;

	UFUNCTION(BlueprintCallable)
	void OnClicked_OptionButton();

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* ExitButton;

	UFUNCTION(BlueprintCallable)
	void OnClicked_ExitButton();
	
#pragma endregion

#pragma region Option

private:
	void InitOption();
protected:
	UFUNCTION(BlueprintCallable)
	void OpenOption();

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpenOptionAnimation;

#pragma endregion

#pragma region Prepare

private:
	void InitPrepare();
protected:
	UFUNCTION(BlueprintCallable)
	void OpenPrepare();

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpenPrePareAnimation;

#pragma endregion

#pragma region Exit

private:
	void InitExit();
protected:
	UFUNCTION(BlueprintCallable)
	void OpenExit();

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpenExitAnimation;
	
	UFUNCTION(BlueprintCallable)
	void ExitGame();

#pragma endregion

};