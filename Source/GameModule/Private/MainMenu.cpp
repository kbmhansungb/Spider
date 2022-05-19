// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "GameModule/GameModule.h"

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
	, BackgroundColor(20U, 20U, 20U, 90U)
{
}

void UMainMenuButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	Button->SetBackgroundColor(BackgroundColor);

	TextBlock->SetText(Text);
	FSlateFontInfo FontInfo = TextBlock->Font;
	FontInfo.Size = TextSize;
	TextBlock->SetFont(FontInfo);
}

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
	, LastAnimation(nullptr)
{
}

void UMainMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitFirst();
	InitMainMenu();
	InitOption();
	InitPrepare();
	InitExit();

	OpenFirst();
}

bool UMainMenu::IsBusy()
{
	return IsPlayingAnimation() == true;
}

void UMainMenu::PlayAnimation(UWidgetAnimation* NewAnimation)
{
	if (LastAnimation == NewAnimation)
	{
		UE_LOG(LogMainMenu, Warning, TEXT("Executed the animation that was running."));
		return;
	}

	if (LastAnimation)
	{
		UUserWidget::PlayAnimation(LastAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}

	if (NewAnimation)
	{
		UUserWidget::PlayAnimation(NewAnimation);
	}
}

void UMainMenu::InitFirst()
{

}

void UMainMenu::OpenFirst()
{
	PlayAnimation(OpenFirstAnimation);
}

void UMainMenu::InitMainMenu()
{
	// MainMenu -> Prepare
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("OnClicked_GameStartButton"));
		GameStartButton->GetButton()->OnClicked.Add(ScriptDelegate);
	}

	// MainMenu -> Option
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("OnClicked_OptionButton"));
		OptionButton->GetButton()->OnClicked.Add(ScriptDelegate);
	}

	// MainMenu -> Exit
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FName("PlayMainMenuToExitAnimation"));
		ExitButton->GetButton()->OnClicked.Add(ScriptDelegate);
	}
}

void UMainMenu::OpenMainMenu()
{
	PlayAnimation(OpenMainMenuAnimation);
}

void UMainMenu::OnClicked_GameStartButton()
{
	if (IsBusy())
	{
		return;
	}

	OpenPrepare();
}

void UMainMenu::OnClicked_OptionButton()
{
	OpenOption();
}

void UMainMenu::OnClicked_ExitButton()
{
	OpenExit();
}

void UMainMenu::InitOption()
{

}

void UMainMenu::OpenOption()
{
	PlayAnimation(OpenOptionAnimation);
}

void UMainMenu::InitPrepare()
{
}

void UMainMenu::OpenPrepare()
{
	PlayAnimation(OpenPrePareAnimation);
}

void UMainMenu::InitExit()
{
	FWidgetAnimationDynamicEvent FinishedScriptDelegate;
	FinishedScriptDelegate.BindUFunction(this, FName("ExitGame"));
	BindToAnimationFinished(OpenExitAnimation, FinishedScriptDelegate);
}

void UMainMenu::OpenExit()
{
	PlayAnimation(OpenExitAnimation);
}

void UMainMenu::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetPlayerContext().GetPlayerController(), EQuitPreference::Quit, true);
}
