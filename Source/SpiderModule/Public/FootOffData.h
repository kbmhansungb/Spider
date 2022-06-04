// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "FootOffData.generated.h"

/*
 *
 */
USTRUCT(BlueprintType)
struct FFootOffData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumOfEnteredFootOffStates;

	FORCEINLINE bool IsFootOff() const
	{
		return NumOfEnteredFootOffStates > 0;
	}
};

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class SPIDERMODULE_API UFootOffDataObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FFootOffData> FootOffDataMap;

public: 
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool IsFootOffState(const FName& StateName) const;

public:
	UFUNCTION(BlueprintCallable)
	void EnterFootOffState(const FName& StateName);

	UFUNCTION(BlueprintCallable)
	void EnterFootOffStates(const TArray<FName>& StateNames);

	UFUNCTION(BlueprintCallable)
	void ExitFootOffState(const FName& StateName);
	
	UFUNCTION(BlueprintCallable)
	void ExitFootOffStates(const TArray<FName>& StateNames);
};

//USTRUCT(BlueprintType)
//struct FFootOffDataObjectInstanced
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
//	UFootOffDataObject* FootOffDataObject;
//};