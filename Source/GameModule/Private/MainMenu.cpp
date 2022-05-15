// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Fonts/SlateFontInfo.h"

#include "Kismet/KismetSystemLibrary.h"

UMainMenuButton::UMainMenuButton(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
	, Text(FText::FromString(FString("Text in here.")))
	, TextSize(33.0f)
	, TextHeightPadding(6.4f)
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
	UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(TextBlock->Slot);
	if (OverlaySlot == nullptr)
	{
		UE_LOG(LogMainMenu, Error, TEXT("TextBlock's parent is not OverlaySlot."));
	}
	else
	{
		OverlaySlot->SetPadding(FMargin(0.0f, TextHeightPadding));
	}
}

float UMainMenuButton::GetDesireHeight()
{
	return TextSize + 2 * TextHeightPadding;
}

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UMainMenu::NativePreConstruct()
{
	FScriptDelegate GameStartButtonDelegate;
	GameStartButtonDelegate.BindUFunction(this, FName("GameStart"));
	GameStartButton->GetButton()->OnClicked.Add(GameStartButtonDelegate);

	FScriptDelegate OptionButtonDelegate;
	OptionButtonDelegate.BindUFunction(this, FName("OpenOptionwidget"));
	OptionButton->GetButton()->OnClicked.Add(OptionButtonDelegate);

	FScriptDelegate ExitButtonDelegate;
	ExitButtonDelegate.BindUFunction(this, FName("ExitGame"));
	ExitButton->GetButton()->OnClicked.Add(ExitButtonDelegate);
}

void UMainMenu::GameStart()
{
	
}

void UMainMenu::OpenOption()
{
	UE_LOG(LogMainMenu, Warning, TEXT("Todo."));
}

void UMainMenu::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetPlayerContext().GetPlayerController(), EQuitPreference::Quit, true);
}
