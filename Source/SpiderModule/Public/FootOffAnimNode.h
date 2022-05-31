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
struct SPIDERMODULE_API FCacheFootOfDataNode : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(BlueprintReadWrite, Transient, Category = CacheFoot, meta = (PinShownByDefault))
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
	FCacheFootOfDataNode Node;

	virtual void CreateOutputPins() override;
};