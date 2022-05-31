// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FootOffData.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FootOffAnimNotifyState.generated.h"

/*
 *
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UFootOffInterface : public UInterface
{
	GENERATED_BODY()
};

class IFootOffInterface
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
UCLASS(MinimalAPI)
class UFootOffFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = Get)
	static UFootOffDataObject* GetFootOfDataObjectFromSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent);

	//UFUNCTION(BlueprintCallable, Category = Edit)
	//static void EnterAnimNotifyState(UFootOffDataObject* FootOffDataObject, const FName& BoneName);

	//UFUNCTION(BlueprintCallable, Category = Edit)
	//static void ExitAnimNotifyState(UFootOffDataObject* FootOffDataObject, const FName& BoneName);
};