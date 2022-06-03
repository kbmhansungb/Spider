// Fill out your copyright notice in the Description page of Project Settings.

#include "FootOffAnimNode.h"	
#include "FootOffData.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationGraphSchema.h"
#include "Kismet/KismetMathLibrary.h"

//////////////////////////////////////////////////////////////////////////

void FCacheFootOffDataNode::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	ComponentPose.Initialize(Context);
}

void FCacheFootOffDataNode::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentPose.CacheBones(Context);
}

void FCacheFootOffDataNode::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FCacheFootOffDataNode::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output)
{
	ComponentPose.EvaluateComponentSpace(Output);
	
	if (!FootOfDataObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FootOfDataObject is not valid."));
		return;
	}

	const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();
	TMap<FName, FFootOffData>& FootOfDataMap = FootOfDataObject->FootOffDataMap;
	for (auto& Pair : FootOfDataMap)
	{
		const FName& BoneName = Pair.Key;
		FFootOffData& FootOffData = Pair.Value;

		//if (FootOffData.NumOfEnteredFootOffStates)
		{
			FCompactPoseBoneIndex CompactPoseBoneIndex(BoneContainer.GetPoseBoneIndexForBoneName(BoneName));
			if (CompactPoseBoneIndex.IsValid() == false)
			{
				UE_LOG(LogTemp, Error, TEXT("BoneName is not valid. So Cann`t find CompactPoseBoneIndex."));
				break;
			}

			const FTransform& ComponentSpace = Output.Pose.GetComponentSpaceTransform(CompactPoseBoneIndex);
			FootOffData.BonePosition_ComponentSpace = ComponentSpace.GetLocation();
		}
	}
}

void FCacheFootOffDataNode::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugData.AddDebugItem(DebugLine);
	ComponentPose.GatherDebugData(DebugData);
}

void UCacheFootOfDataGraphNode::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("ComponentPose"));
}

//////////////////////////////////////////////////////////////////////////

void FCacheBoneTransformFromReferenceNode::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	ComponentPose.Initialize(Context);

	FBoneContainer& RequiredBones = Context.AnimInstanceProxy->GetRequiredBones();
	for (auto& BoneReference : TargetBoneArray)
	{
		BoneReference.Initialize(RequiredBones);
	}
}

void FCacheBoneTransformFromReferenceNode::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentPose.CacheBones(Context);
}

void FCacheBoneTransformFromReferenceNode::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FCacheBoneTransformFromReferenceNode::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output)
{
	ComponentPose.EvaluateComponentSpace(Output);

	if (!FootOfDataObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FootOfDataObject is not valid."));
		return;
	}

	const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();
	for (const auto& BoneReference : TargetBoneArray)
	{
		FFootOffData& FootOffData = FootOfDataObject->FootOffDataMap.FindOrAdd(BoneReference.BoneName);
		FCompactPoseBoneIndex CompactPoseBoneIndex(BoneContainer.GetPoseBoneIndexForBoneName(BoneReference.BoneName));
		if (CompactPoseBoneIndex == INDEX_NONE)
		{
			break;
		}
		const FTransform& BoneTransform = Output.Pose.GetComponentSpaceTransform(CompactPoseBoneIndex);

		FootOffData.BonePosition_ComponentSpace = BoneTransform.GetLocation();
	}
}

void FCacheBoneTransformFromReferenceNode::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugData.AddDebugItem(DebugLine);
	ComponentPose.GatherDebugData(DebugData);
}

void UCacheBoneTransformFromReferenceGraphNode::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("ComponentPose"));
}

//////////////////////////////////////////////////////////////////////////

void FLineTraceFromBoneNode::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	ComponentPose.Initialize(Context);

	FBoneContainer& RequiredBones = Context.AnimInstanceProxy->GetRequiredBones();

	for (auto& LineTraceFromBoneInfo : LineTraceFromBoneInfoArray)
	{
		LineTraceFromBoneInfo.FromBone.Initialize(RequiredBones);
		LineTraceFromBoneInfo.ToBone.Initialize(RequiredBones);
	}
}

void FLineTraceFromBoneNode::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentPose.CacheBones(Context);
}

void FLineTraceFromBoneNode::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FLineTraceFromBoneNode::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output)
{
	ComponentPose.EvaluateComponentSpace(Output);

	if (!FootOfDataObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FootOfDataObject is not valid."));
		return;
	}

	FBoneContainer& RequiredBones = Output.AnimInstanceProxy->GetRequiredBones();
	USkeletalMeshComponent* SkeletalMeshComponent = Output.AnimInstanceProxy->GetSkelMeshComponent();
	const FTransform& ComponentToWorld = SkeletalMeshComponent->GetComponentToWorld();


	for (auto& Info : LineTraceFromBoneInfoArray)
	{
		FFootOffTraceResult& TraceResult = FootOfDataObject->TraceResultMap.FindOrAdd(Info.TracedName);

		if (Info.FromBone.IsValidToEvaluate() && Info.ToBone.IsValidToEvaluate())
		{
			FTransform FromLocation = Output.Pose.GetComponentSpaceTransform(Info.FromBone.GetCompactPoseIndex(RequiredBones));
			FTransform ToLocation = Output.Pose.GetComponentSpaceTransform(Info.ToBone.GetCompactPoseIndex(RequiredBones));

			FromLocation *= ComponentToWorld;
			ToLocation *= ComponentToWorld;

			FVector StartPosition = FromLocation.GetLocation();
			FVector Direction = ToLocation.GetLocation() - FromLocation.GetLocation();
			Direction.Normalize();
			Direction *= Info.MaxLength;
			FVector EndPosition = StartPosition + Direction;

			FCollisionQueryParams Params;
			Params.AddIgnoredActor(SkeletalMeshComponent->GetOwner());
			TraceResult.IsHit = SkeletalMeshComponent->GetWorld()->LineTraceSingleByChannel(
				TraceResult.HitResult, StartPosition, EndPosition, ECollisionChannel::ECC_WorldStatic, Params);

			TraceResult.FixedPosition_WorldSpace = TraceResult.IsHit ? TraceResult.HitResult.Location : EndPosition;


#ifdef UE_ENABLE_DEBUG_DRAWING 

			// Debug draw
			const FColor& Color = TraceResult.IsHit ? FColor::Green : FColor::Red;
			DrawDebugDirectionalArrow(SkeletalMeshComponent->GetWorld(), StartPosition, TraceResult.FixedPosition_WorldSpace, 5.0f, Color);

#endif // UE_ENABLE_DEBUG_DRAWING 
		}
	}
}

void FLineTraceFromBoneNode::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugData.AddDebugItem(DebugLine);
	ComponentPose.GatherDebugData(DebugData);
}

void ULineTraceFromBoneGraphNode::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("ComponentPose"));
}

//////////////////////////////////////////////////////////////////////////


void FLineTraceFromAxisNode::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	ComponentPose.Initialize(Context);

	FBoneContainer& RequiredBones = Context.AnimInstanceProxy->GetRequiredBones();

	for (auto& LineTraceFromBoneInfo : LineTraceFromBoneInfoArray)
	{
		LineTraceFromBoneInfo.TargetBone.Initialize(RequiredBones);
	}
}

void FLineTraceFromAxisNode::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentPose.CacheBones(Context);
}

void FLineTraceFromAxisNode::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FLineTraceFromAxisNode::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output)
{
	ComponentPose.EvaluateComponentSpace(Output);

	if (!FootOfDataObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FootOfDataObject is not valid."));
		return;
	}

	FBoneContainer& RequiredBones = Output.AnimInstanceProxy->GetRequiredBones();
	USkeletalMeshComponent* SkeletalMeshComponent = Output.AnimInstanceProxy->GetSkelMeshComponent();
	const FTransform& ComponentToWorld = SkeletalMeshComponent->GetComponentToWorld();


	for (auto& Info : LineTraceFromBoneInfoArray)
	{
		FFootOffTraceResult& TraceResult = FootOfDataObject->TraceResultMap.FindOrAdd(Info.TracedName);

		if (!Info.TargetBone.IsValidToEvaluate())
		{
			break;
		}

		FVector StartPosition, EndPosition;

		const FTransform& Transform_ComponentSpace = Output.Pose.GetComponentSpaceTransform(Info.TargetBone.GetCompactPoseIndex(RequiredBones));
		if (IsUpdatePosition)
		{
			FTransform Location = Transform_ComponentSpace * ComponentToWorld;
			TraceResult.BonePosition_WorldSpace = Location.GetLocation();
		}
		StartPosition = TraceResult.BonePosition_WorldSpace - Axis * Info.StartOffset;
		EndPosition = StartPosition + Axis * Info.MaxLength;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SkeletalMeshComponent->GetOwner());
		TraceResult.IsHit = SkeletalMeshComponent->GetWorld()->LineTraceSingleByChannel(
			TraceResult.HitResult, StartPosition, EndPosition, ECollisionChannel::ECC_WorldStatic, Params);

		if (TraceResult.IsHit)
		{
			FVector Offset = UKismetMathLibrary::ProjectVectorOnToVector(Transform_ComponentSpace.GetLocation(), Axis);
			TraceResult.FixedPosition_WorldSpace = TraceResult.HitResult.Location + Offset * OffsetMultifly;
		}
		else
		{
			TraceResult.FixedPosition_WorldSpace = IsReturnEndPositionWhenNotHit ? EndPosition : TraceResult.BonePosition_WorldSpace;
		}

		// Todo : Debug Draw line을 AnimInstance의 Update로 옮겨야함.
#ifdef UE_ENABLE_DEBUG_DRAWING 

		// Draw trace line
		const FColor& Color = TraceResult.IsHit ? FColor::Green : FColor::Red;
		DrawDebugDirectionalArrow(SkeletalMeshComponent->GetWorld(), StartPosition, TraceResult.IsHit ? TraceResult.HitResult.Location : EndPosition, 5.0f, Color);

#endif // UE_ENABLE_DEBUG_DRAWING 
	}
}

void FLineTraceFromAxisNode::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugData.AddDebugItem(DebugLine);
	ComponentPose.GatherDebugData(DebugData);
}

void ULineTraceFromAxisGraphNode::CreateOutputPins()
{
	//CreatePin(EGPD_Input, UAnimationGraphSchema::Vector3fStruct, TEXT("Axis"));
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("ComponentPose"));
}