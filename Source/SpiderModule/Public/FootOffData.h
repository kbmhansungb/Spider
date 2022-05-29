// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FootOffData.generated.h"

/*
 *
 */
USTRUCT(BlueprintType)
struct FFootOfData
{
	GENERATED_BODY()
public:
	FFootOfData()
		: OriginalPosition(), HitPosition(), IsFootOffState(false), IsHit(false)
	{}
	FFootOfData(const FVector& OriginalPosition, const FVector& HitPosition, bool IsFootOffState, bool IsHit)
		: OriginalPosition(OriginalPosition), HitPosition(HitPosition), IsFootOffState(IsFootOffState), IsHit(IsHit)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginalPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HitPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFootOffState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHit;
};

UCLASS(BlueprintType)
class SPIDERMODULE_API UFootOffDataObject final : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform ComponentSpaceToRelativeTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform ComponentSpaceToWorldTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FFootOfData> FootOfDataMap;
};