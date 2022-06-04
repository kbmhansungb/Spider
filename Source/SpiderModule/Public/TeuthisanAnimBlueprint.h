// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimNode_Trace.h"
#include "FootOffAnimNotifyState.h"
#include "TeuthisanAnimBlueprint.generated.h"

UCLASS()
class SPIDERMODULE_API UTheuthisanAnimBlueprint : public UAnimInstance, public IFootOffInterface
{
	GENERATED_BODY()

public:
	UTheuthisanAnimBlueprint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UFootOffDataObject* FootOfDataObject;

public:
	virtual UFootOffDataObject* GetFootOfDataObject_Implementation() override;
};