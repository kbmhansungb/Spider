// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "AnimGraphNode_Base.h"
#include "AnimNode_Trace.generated.h"

/*
 *
 */
USTRUCT(BlueprintType)
struct SPIDERMODULE_API FTraceAnimNodeResult
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

/*
 *
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class UTracedDataObject final : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FTraceAnimNodeResult> TracedResultMap;
};

USTRUCT(BlueprintType)
struct FTracedDataObjectInstanced
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UTracedDataObject* TracedDataObject;
};

USTRUCT(BlueprintType)
struct SPIDERMODULE_API FTraceAnimNodeMeta
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TracedName;

	UPROPERTY(EditAnywhere, Category = TraceStart)
	FBoneReference TargetBone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TraceInfo)
	float TracedLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TraceInfo)
	float StartOffset;

	FORCEINLINE void InitializeBoneReference(const FBoneContainer& RequiredBones)
	{
		TargetBone.Initialize(RequiredBones);
	}
};

/*
 *
 */
USTRUCT(BlueprintInternalUseOnly)
struct SPIDERMODULE_API FTrace_AnimNode : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (AlwaysAsPin))
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = Links, meta = (PinShownByDefault))
	TWeakObjectPtr<UTracedDataObject> TracedDataObject = nullptr;
	
	UPROPERTY(EditAnywhere, Category = TraceInfo)
	TArray<FTraceAnimNodeMeta> LineTraceFromBoneInfoArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TraceInfo, meta = (PinShownByDefault))
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BonePositionOption, meta = (PinShownByDefault))
	bool IsUpdatePosition = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FixedPositionOption, meta = (PinShownByDefault))
	float OffsetMultifly = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FixedPositionOption, meta = (PinShownByDefault))
	bool IsReturnEndPositionWhenNotHit = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FixedPositionOption, meta = (PinShownByDefault))
	bool UseFixedPositionInterp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FixedPositionOption, meta = (PinShownByDefault))
	float MaxInterpolateLength = 10.0f;

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	
protected:
	FVector InterpolatePositionWithAxis(const FVector& Axis, const FVector& BeforePosition, const FVector& NewPosition, float MaxLength);
};

UCLASS(MinimalAPI)
class UTrace_AnimGraphNode : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FTrace_AnimNode Node;

	virtual void CreateOutputPins() override;
};