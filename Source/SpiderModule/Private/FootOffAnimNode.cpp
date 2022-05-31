// Fill out your copyright notice in the Description page of Project Settings.

#include "FootOffAnimNode.h"	
#include "FootOffData.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationGraphSchema.h"

void FCacheFootOfDataNode::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	ComponentPose.Initialize(Context);
}

void FCacheFootOfDataNode::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentPose.CacheBones(Context);
}

void FCacheFootOfDataNode::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FCacheFootOfDataNode::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output)
{
	ComponentPose.EvaluateComponentSpace(Output);
	
	if (!FootOfDataObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FootOfDataObject is not valid."));
		return;
	}

	const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();
	TMap<FName, FFootOfData>& FootOfDataMap = FootOfDataObject->FootOfDataMap;
	for (auto& Pair : FootOfDataMap)
	{
		const FName& BoneName = Pair.Key;
		FFootOfData& FootOffData = Pair.Value;

		//if (FootOffData.NumOfEnteredFootOffStates)
		{
			FCompactPoseBoneIndex CompactPoseBoneIndex(BoneContainer.GetPoseBoneIndexForBoneName(BoneName));
			if (CompactPoseBoneIndex.IsValid() == false)
			{
				UE_LOG(LogTemp, Error, TEXT("BoneName is not valid. So Cann`t find CompactPoseBoneIndex."));
				break;
			}

			FTransform ComponentSpace = Output.Pose.GetComponentSpaceTransform(CompactPoseBoneIndex);
			FootOffData.BonePosition_ComponentSpace = ComponentSpace.GetLocation();
		}
	}
}

void FCacheFootOfDataNode::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugData.AddDebugItem(DebugLine);
	ComponentPose.GatherDebugData(DebugData);
}

void UCacheFootOfDataGraphNode::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("ComponentPose"));
}
