// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


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
	TextBlock->Font.Size = TextSize;
	UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(TextBlock->Slot);
	OverlaySlot->SetPadding(FMargin(0.0f, TextHeightPadding));
}