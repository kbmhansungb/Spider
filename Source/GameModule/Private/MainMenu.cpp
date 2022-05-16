// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

#include "Components/TextBlock.h"
#include "Fonts/SlateFontInfo.h"

#include "Components/Button.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Animation/WidgetAnimation.h"

UMainMenuButton::UMainMenuButton(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
	, Text(FText::FromString(FString("Text in here.")))
	, TextSize(33.0f)
	//, TextHeightPadding(6.4f)
	, BackgroundColor(20U, 20U, 20U, 90U)
{
}

void UMainMenuButton::NativePreConstruct()
{
	Button->SetBackgroundColor(BackgroundColor);

	TextBlock->SetText(Text);
	FSlateFontInfo FontInfo = TextBlock->Font;
	FontInfo.Size = TextSize;
	TextBlock->SetFont(FontInfo);
	//UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(TextBlock->Slot);
	//if (OverlaySlot == nullptr)
	//{
	//	UE_LOG(LogMainMenu, Error, TEXT("TextBlock's parent is not OverlaySlot."));
	//}
	//else
	//{
	//	OverlaySlot->SetPadding(FMargin(0.0f, TextHeightPadding));
	//}
}

//float UMainMenuButton::GetDesireHeight()
//{
//	return TextSize + 2 * TextHeightPadding;
//}

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UMainMenu::NativePreConstruct()
{
	// MainMenu -> Prepare
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("PlayMainMenuToPrepareAnimation"));
		GameStartButton->GetButton()->OnClicked.Add(ScriptDelegate);
	}

	// MainMenu -> Option
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("PlayMainMenuToOptionAnimation"));
		OptionButton->GetButton()->OnClicked.Add(ScriptDelegate);
	}

	// MainMenu -> Exit
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("PlayMainMenuToExitAnimation"));
		ExitButton->GetButton()->OnClicked.Add(ScriptDelegate);
	}
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// First -> MainMenu
	PlayFirstToMainMenuAnimation();
}

bool UMainMenu::IsBusy()
{
	return IsPlayingAnimation() == true;
}

void UMainMenu::Prepare()
{
}

void UMainMenu::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetPlayerContext().GetPlayerController(), EQuitPreference::Quit, true);
}

void UMainMenu::OnClicked_StartGame()
{
	if (IsBusy())
	{
		return;
	}

	UE_LOG(LogMainMenu, Warning, TEXT("Todo."));
}

void UMainMenu::PlayFirstToMainMenuAnimation()
{
	PlayAnimation(FirstToMainMenuAnimation);
}

void UMainMenu::PlayReadyToPlayAnimation()
{
	PlayAnimation(ReadyToPlayAnimation);
}

void UMainMenu::PlayMainMenuToPrepareAnimation()
{
	UnbindAllFromAnimationFinished(MainMenuToPrepareAnimation);
	FScriptDelegate StartScriptDelegate;
	StartScriptDelegate.BindUFunction(this, FName("Prepare"));
	BindToAnimationStarted(MainMenuToPrepareAnimation, FWidgetAnimationDynamicEvent(StartScriptDelegate));

	UnbindAllFromAnimationFinished(MainMenuToPrepareAnimation);
	FScriptDelegate FinishScriptDelegate;
	FinishScriptDelegate.BindUFunction(this, FName("PlayReadyToPlayAnimation"));
	BindToAnimationFinished(MainMenuToPrepareAnimation, FWidgetAnimationDynamicEvent(FinishScriptDelegate));

	PlayAnimation(MainMenuToPrepareAnimation);
}

void UMainMenu::PlayMainMenuToOptionAnimation()
{
	PlayAnimation(MainMenuToOptionAnimation);
}

void UMainMenu::PlayOptionToMainMenuAnimation()
{
	PlayAnimation(MainMenuToOptionAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
}

void UMainMenu::PlayMainMenuToExitAnimation()
{
	UnbindAllFromAnimationFinished(MainMenuToExitAnimation);
	FScriptDelegate FinishScriptDelegate;
	FinishScriptDelegate.BindUFunction(this, FName("ExitGame"));
	BindToAnimationFinished(MainMenuToExitAnimation, FWidgetAnimationDynamicEvent(FinishScriptDelegate));
	
	PlayAnimation(MainMenuToExitAnimation);
}
