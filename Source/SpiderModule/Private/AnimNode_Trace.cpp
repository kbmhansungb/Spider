// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNode_Trace.h"	
#include "FootOffData.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationGraphSchema.h"
#include "Kismet/KismetMathLibrary.h"

void FTrace_AnimNode::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	ComponentPose.Initialize(Context);

	const FBoneContainer& RequiredBones = Context.AnimInstanceProxy->GetRequiredBones();
	
	for (auto& LineTraceFromBoneInfo : LineTraceFromBoneInfoArray)
	{
		LineTraceFromBoneInfo.InitializeBoneReference(RequiredBones);
	}
}

void FTrace_AnimNode::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	ComponentPose.CacheBones(Context);
}

void FTrace_AnimNode::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FTrace_AnimNode::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output)
{
	ComponentPose.EvaluateComponentSpace(Output);

	if (!TracedDataObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("FootOfDataObject is not valid."));
		return;
	}

	const FBoneContainer& RequiredBones = Output.AnimInstanceProxy->GetRequiredBones();
	const USkeletalMeshComponent* SkeletalMeshComponent = Output.AnimInstanceProxy->GetSkelMeshComponent();
	const FTransform& ComponentToWorld = SkeletalMeshComponent->GetComponentToWorld();
	
	
	for (auto& Info : LineTraceFromBoneInfoArray)
	{
		FTraceAnimNodeResult& TraceResult = TracedDataObject->TracedResultMap.FindOrAdd(Info.TracedName);

		if (!Info.TargetBone.IsValidToEvaluate())
		{
			break;
		}

		FVector StartPosition, EndPosition;

		// Update BonePosition
		const FTransform& Transform_ComponentSpace = Output.Pose.GetComponentSpaceTransform(Info.TargetBone.GetCompactPoseIndex(RequiredBones));
		if (IsUpdatePosition)
		{
			FTransform Location = Transform_ComponentSpace * ComponentToWorld;
			TraceResult.BonePosition_WorldSpace = Location.GetLocation();
		}
		StartPosition = TraceResult.BonePosition_WorldSpace - Direction * Info.StartOffset;
		EndPosition = StartPosition + Direction * Info.TracedLength;

		// Trace
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SkeletalMeshComponent->GetOwner());
		TraceResult.IsHit = SkeletalMeshComponent->GetWorld()->LineTraceSingleByChannel(
			TraceResult.HitResult, StartPosition, EndPosition, ECollisionChannel::ECC_WorldStatic, Params);

		// Update FixedPosition
		FVector NewFixedPosition;
		if (TraceResult.IsHit)
		{
			FVector Offset = UKismetMathLibrary::ProjectVectorOnToVector(Transform_ComponentSpace.GetLocation(), Direction);
			NewFixedPosition = TraceResult.HitResult.Location + Offset * OffsetMultifly;
		}
		else
		{
			NewFixedPosition = IsReturnEndPositionWhenNotHit ? EndPosition : TraceResult.BonePosition_WorldSpace;
		}

		TraceResult.FixedPosition_WorldSpace = 
			UseFixedPositionInterp 
			? InterpolatePositionWithAxis(Direction, TraceResult.FixedPosition_WorldSpace, NewFixedPosition, MaxInterpolateLength)
			: NewFixedPosition;

//#ifdef UE_ENABLE_DEBUG_DRAWING 
//
//		// Draw trace line
//		const FColor& Color = TraceResult.IsHit ? FColor::Green : FColor::Red;
//		DrawDebugLine(SkeletalMeshComponent->GetWorld(), StartPosition, TraceResult.IsHit ? TraceResult.HitResult.Location : EndPosition, Color);
//
//#endif // UE_ENABLE_DEBUG_DRAWING 
	}
}

void FTrace_AnimNode::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);

	DebugData.AddDebugItem(DebugLine);
	ComponentPose.GatherDebugData(DebugData);
}

FVector FTrace_AnimNode::InterpolatePositionWithAxis(const FVector& Axis, const FVector& BeforePosition, const FVector& NewPosition, float MaxLength)
{
	FVector ToVector = NewPosition - BeforePosition;
	FVector ProjectToAxis = ToVector.ProjectOnTo(Axis);
	FVector ResultPosition;

	float VectorLength = ProjectToAxis.Length();
	if (ProjectToAxis.Normalize())
	{
		ResultPosition = BeforePosition + ToVector - ProjectToAxis * VectorLength;

		if (MaxLength > VectorLength)
		{
			ResultPosition += ProjectToAxis * VectorLength;
		}
		else
		{
			ResultPosition += ProjectToAxis * MaxLength;
		}
	}
	else
	{
		ResultPosition = NewPosition;
	}

	return ResultPosition;
}

void UTrace_AnimGraphNode::CreateOutputPins()
{
	//CreatePin(EGPD_Input, UAnimationGraphSchema::Vector3fStruct, TEXT("Axis"));
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("ComponentPose"));
}