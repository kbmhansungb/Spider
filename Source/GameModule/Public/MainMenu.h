// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UOverlay;
class UTextBlock;
class UButton;

/*
 * 
 */
UCLASS(BlueprintType)
class GAMEMODULE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
};

/*
*
*/
UCLASS(BlueprintType)
class GAMEMODULE_API UMainMenuButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuButton(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor BackgroundColor;

protected:
	virtual void NativePreConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;

	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
};