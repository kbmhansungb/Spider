// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FootOffAnimNotifyState.h"
#include "TeuthisanAnimBlueprint.generated.h"

UCLASS()
class SPIDERMODULE_API UTheuthisanAnimBlueprint : public UAnimInstance, public IReactToFeetOffInterface
{
	GENERATED_BODY()

public:
	UTheuthisanAnimBlueprint();
	//virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFootOffDataObject* FootOfDataObject;

public:
	virtual UFootOffDataObject* GetFootOfDataObject_Implementation() override;
};