// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
//#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimGraphNode_Base.h"
#include "FootOffData.h"
#include "FootOffAnimNode.generated.h"

/*
 *
 */
USTRUCT(BlueprintInternalUseOnly)
struct SPIDERMODULE_API FCacheFootOffDataNode : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = CacheFootOff, meta = (PinShownByDefault))
	TWeakObjectPtr<UFootOffDataObject> FootOfDataObject = nullptr;

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
};

UCLASS(MinimalAPI)
class UCacheFootOfDataGraphNode : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FCacheFootOffDataNode Node;

	virtual void CreateOutputPins() override;
};

/*
 *
 */
USTRUCT(BlueprintInternalUseOnly)
struct SPIDERMODULE_API FCacheBoneTransformFromReferenceNode : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(EditAnywhere)
	TArray<FBoneReference> TargetBoneArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = CacheFootOff, meta = (PinShownByDefault))
	TWeakObjectPtr<UFootOffDataObject> FootOfDataObject = nullptr;

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
};

UCLASS(MinimalAPI)
class UCacheBoneTransformFromReferenceGraphNode : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FCacheBoneTransformFromReferenceNode Node;

	virtual void CreateOutputPins() override;
};

USTRUCT(BlueprintType)
struct SPIDERMODULE_API FLineTraceFromBoneInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TracedName;

	UPROPERTY(EditAnywhere)
	FBoneReference FromBone;

	UPROPERTY(EditAnywhere)
	FBoneReference ToBone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLength;
};

/*
 *
 */
USTRUCT(BlueprintInternalUseOnly)
struct SPIDERMODULE_API FLineTraceFromBoneNode : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = CacheFootOff, meta = (PinShownByDefault))
	TWeakObjectPtr<UFootOffDataObject> FootOfDataObject = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<FLineTraceFromBoneInfo> LineTraceFromBoneInfoArray;

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
};

UCLASS(MinimalAPI)
class ULineTraceFromBoneGraphNode : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FLineTraceFromBoneNode Node;

	virtual void CreateOutputPins() override;
};


USTRUCT(BlueprintType)
struct SPIDERMODULE_API FLineTraceFromAxisInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TracedName;

	UPROPERTY(EditAnywhere)
	FBoneReference TargetBone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
struct SPIDERMODULE_API FLineTraceFromAxisNode : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (AlwaysAsPin))
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = Links, meta = (PinShownByDefault))
	TWeakObjectPtr<UFootOffDataObject> FootOfDataObject = nullptr;

	UPROPERTY(EditAnywhere, Category = TraceInfo)
	TArray<FLineTraceFromAxisInfo> LineTraceFromBoneInfoArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TraceInfo, meta = (PinShownByDefault))
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BonePositionOption, meta = (PinShownByDefault))
	bool IsUpdatePosition = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FixedPositionOption, meta = (PinShownByDefault))
	float OffsetMultifly = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FixedPositionOption, meta = (PinShownByDefault))
	bool IsReturnEndPositionWhenNotHit = false;

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
};

UCLASS(MinimalAPI)
class ULineTraceFromAxisGraphNode : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FLineTraceFromAxisNode Node;

	virtual void CreateOutputPins() override;
};