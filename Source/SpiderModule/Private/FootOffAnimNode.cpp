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

	USkeletalMeshComponent* SkeletalMeshComponent = Output.AnimInstanceProxy->GetSkelMeshComponent();
	//int32 BoneIndex = Output.AnimInstanceProxy->GetSkeleton()->GetReferenceSkeleton().FindBoneIndex(SocketName);
	//FBoneReference BoneReference = Output.AnimInstanceProxy->GetRequiredBones();
	//if (BoneIndex == INDEX_NONE)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Bone Index is not valid."));
	//	return;
	//}

	// ComponentSpace
	const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();
	FTransform ComponentSpace = Output.Pose.GetComponentSpaceTransform(FCompactPoseBoneIndex(BoneContainer.GetPoseBoneIndexForBoneName(SocketName)));
	//FTransform ComponentSpace = Output.Pose.GetLocalSpaceTransform(FCompactPoseBoneIndex(BoneIndex));

	// ComponentSpace to Relative
	FootOfDataObject->ComponentSpaceToRelativeTransform = FTransform(SkeletalMeshComponent->GetRelativeRotation(), SkeletalMeshComponent->GetRelativeLocation(), SkeletalMeshComponent->GetRelativeScale3D());

	// ComponentSpace to World
	//FootOfDataObject->ComponentSpaceToWorldTransform = FTransform(SkeletalMeshComponent->TransformFromBoneSpace())
	
	// Cache ComponentSpace
	//FootOfDataObject->FootOfDataMap.FindOrAdd(SocketName).OriginalPosition = (FootOfDataObject->ComponentSpaceToRelativeTransform * ComponentSpace).GetLocation();
	FootOfDataObject->FootOfDataMap.FindOrAdd(SocketName).OriginalPosition = (ComponentSpace * SkeletalMeshComponent->GetComponentToWorld()).GetLocation();
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
