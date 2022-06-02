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
	FName CombinedEnteredFootOffStateBone;

	/*
	 * It must be stetted when the update is called.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BonePosition_ComponentSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BonePosition_WorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TracedPosition_WorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector FixedPosition_WorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult HitResult;

	// Todo
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFootOffHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxTracedLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumOfEnteredFootOffStates;

	FORCEINLINE bool IsFootOff()
	{
		return NumOfEnteredFootOffStates > 0;
	}
};

/*
 *
 */
USTRUCT(BlueprintType)
struct SPIDERMODULE_API FFootOffTraceResult
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BonePosition_WorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector FixedPosition_WorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult HitResult;
};

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class SPIDERMODULE_API UFootOffDataObject final : public UObject
{
	GENERATED_BODY()

public:
	///*
	// * 
	// */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FFootOffData> FootOffDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FFootOffTraceResult> TraceResultMap;

	UFUNCTION(BlueprintCallable)
	void UpdateFootOffData(USkeletalMeshComponent* SkeletalMeshComponent);

	UFUNCTION(BlueprintCallable)
	void EnterFootOffState(const FName& BoneName);

	UFUNCTION(BlueprintCallable)
	void EnterFootOffStates(const TArray<FName>& BoneNames);

	UFUNCTION(BlueprintCallable)
	void ExitFootOffState(const FName& BoneName);
	
	UFUNCTION(BlueprintCallable)
	void ExitFootOffStates(const TArray<FName>& BoneNames);

	UFUNCTION(BlueprintCallable)
	void UpdateFootOffDataFromNotifyState(const FName& BoneName, bool IsUpdateMaxFootOffHeight);
};