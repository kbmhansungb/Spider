// Fill out your copyright notice in the Description page of Project Settings.

#include "FootOffAnimNotifyState.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "CollisionQueryParams.h"
#include "FootOffData.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animation/AnimInstance.h"


UFootOffDataObject* UFootOffFunctionLibrary::GetFootOfDataObjectFromSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (!AnimInstance)
	{
		//UE_LOG(LogTemp, Error, TEXT("AnimInstance is not valid."));
		return nullptr;
	}

	IFootOffInterface* ReactToFeetOffInterface = Cast<IFootOffInterface>(AnimInstance);
	if (!ReactToFeetOffInterface)
	{
		//UE_LOG(LogTemp, Error, TEXT("AnimInstance is not implement ReactToFeetOffInterface."));
		return nullptr;
	}
	return IFootOffInterface::Execute_GetFootOfDataObject(AnimInstance);
}

//void UFootOffAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
//{
//	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
//}
//
//void UFootOffAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
//{
//	Super::NotifyEnd(MeshComp, Animation, EventReference);
//}
//
//void UFootOffAnimNotifyState::OnAnimNotifyCreatedInEditor(FAnimNotifyEvent& ContainingAnimNotifyEvent)
//{
//	//const UAnimSequence* AnimSequence = Cast<const UAnimSequence>(ContainingAnimNotifyEvent.GetLinkedSequence());
//	//const FReferenceSkeleton RefSkeleton = AnimSequence->GetSkeleton()->GetReferenceSkeleton();
//
//	//BoneOffset_ComponentSpace = GetComponentSpaceTransform(RefSkeleton, AnimSequence, ContainingAnimNotifyEvent.TrackIndex, ContainingAnimNotifyEvent.GetEndTriggerTime(), Boneindex);
//}
//
//FTransform UFootOffAnimNotifyState::GetComponentSpaceTransform(const FReferenceSkeleton& RefSkeleton, const UAnimSequence* AnimSequence, int32 TrackIndex, float Time, int32 BoneIndex) const
//{
//	int32 ParentBone = RefSkeleton.GetParentIndex(BoneIndex);
//	
//	FTransform ComponentSpaceTransform;
//	AnimSequence->GetBoneTransform(ComponentSpaceTransform, TrackIndex, Time, false);
//
//	if (ParentBone != INDEX_NONE)
//	{
//		ComponentSpaceTransform *= GetComponentSpaceTransform(RefSkeleton, AnimSequence, TrackIndex, Time, BoneIndex);
//	}
//
//	return ComponentSpaceTransform;
//}
