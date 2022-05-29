// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FootOffData.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"
#include "FootOffAnimNotifyState.generated.h"

/*
 *
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UReactToFeetOffInterface : public UInterface
{
	GENERATED_BODY()
};

class IReactToFeetOffInterface
{
	GENERATED_BODY()

public:
	/** Add interface function declarations here */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UFootOffDataObject* GetFootOfDataObject();
	virtual UFootOffDataObject* GetFootOfDataObject_Implementation() { return nullptr; };
};

/*
 *
 */
UCLASS(Abstract)
class SPIDERMODULE_API UFootOffStateBase : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	bool GetBoneHitResult(USkeletalMeshComponent* SkeletalMeshComponent, const FName& BoneName, FHitResult& HItResult, FVector& OriginalPosition);

	UFUNCTION(BlueprintCallable)
	void UpdateBonePosition(USkeletalMeshComponent* SkeletalMeshComponent, const FName& BoneName);
};