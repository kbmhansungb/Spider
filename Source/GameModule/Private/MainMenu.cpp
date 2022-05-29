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

#include "TimerManager.h"

UMainMenuButton::UMainMenuButton(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
	, Text(FText::FromString(FString("Text in here.")))
	, TextSize(33.0f)
{
}

void UMainMenuButton::NativePreConstruct()
{
	Super::NativePreConstruct();

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

	//OpenFirst();
	ProcessFirst();
}

bool UMainMenu::IsBusy()
{
	return IsPlayingAnimation() == true;
}

void UMainMenu::PlayMainMenuAniamtion(UWidgetAnimation* NewAnimation)
{
	if (LastAnimation == NewAnimation)
	{
		UE_LOG(LogMainMenu, Warning, TEXT("Executed the animation that was running."));
		return;
	}

	if (LastAnimation)
	{
		PlayAnimation(LastAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}

	if (NewAnimation)
	{
		PlayAnimation(NewAnimation);
		LastAnimation = NewAnimation;
	}
}

void UMainMenu::SetForceMainMenuAnimation(UWidgetAnimation* NewAnimation)
{
	LastAnimation = NewAnimation;
}

void UMainMenu::InitFirst()
{
	//FWidgetAnimationDynamicEvent FinishedScriptDelegate;
	//FinishedScriptDelegate.BindUFunction(this, FName("ProcessFirst"));
	//BindToAnimationFinished(OpenFirstAnimation, FinishedScriptDelegate);
}

//void UMainMenu::OpenFirst()
//{
//	IsNotEqualLastAnimation(OpenFirstAnimation);
//
//	PlayMainMenuAniamtion(OpenFirstAnimation);
//}

bool TestDelay = false;

void UMainMenu::ProcessFirst()
{
	SetForceMainMenuAnimation(OpenFirstAnimation);
	
	FTimerHandle LoopTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(LoopTimerHandle, [this]() { this->ProcessLoop(); }, 0.03f, false);

	FTimerHandle ConstDelayTimerHandle;
	TestDelay = false;
	GetWorld()->GetTimerManager().SetTimer(ConstDelayTimerHandle, []() { TestDelay = true; }, 2.0f, false);
}

void UMainMenu::ProcessLoop()
{
	bool IsLoading = true;

	if (TestDelay)
	{
		IsLoading = false;
	}

	if (IsLoading)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() { this->ProcessLoop(); }, 0.03f, false);
	}
	else
	{
		OpenMainMenu();
	}
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
		ScriptDelegate.BindUFunction(this, FName("OpenExit"));
		ExitButton->GetButton()->OnClicked.Add(ScriptDelegate);
	}
}

void UMainMenu::OpenMainMenu()
{
	PlayMainMenuAniamtion(OpenMainMenuAnimation);
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
	PlayMainMenuAniamtion(OpenOptionAnimation);
}

void UMainMenu::InitPrepare()
{
}

void UMainMenu::OpenPrepare()
{
	PlayMainMenuAniamtion(OpenPrePareAnimation);
}

void UMainMenu::InitExit()
{
	FWidgetAnimationDynamicEvent FinishedScriptDelegate;
	FinishedScriptDelegate.BindUFunction(this, FName("ExitGame"));
	BindToAnimationFinished(OpenExitAnimation, FinishedScriptDelegate);
}

void UMainMenu::OpenExit()
{
	PlayMainMenuAniamtion(OpenExitAnimation);
}

void UMainMenu::ExitGame()
{
	UE_LOG(LogMainMenu, Display, TEXT("Exit game is called."));
	UKismetSystemLibrary::QuitGame(this, GetPlayerContext().GetPlayerController(), EQuitPreference::Quit, true);
}
