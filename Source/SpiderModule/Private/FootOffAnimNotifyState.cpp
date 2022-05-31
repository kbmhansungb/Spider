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

//void UFootOffFunctionLibrary::EnterAnimNotifyState(UFootOffDataObject* FootOffDataObject, const FName& BoneName)
//{
//	if (!FootOffDataObject)
//	{
//		UE_LOG(LogTemp, Error, TEXT("FootOffDataObject is not valid."));
//		return;
//	}
//
//	FootOffDataObject->EnterFootOffState(BoneName);
//}
//
//void UFootOffFunctionLibrary::ExitAnimNotifyState(UFootOffDataObject* FootOffDataObject, const FName& BoneName)
//{
//	if (!FootOffDataObject)
//	{
//		UE_LOG(LogTemp, Error, TEXT("FootOffDataObject is not valid."));
//		return;
//	}
//
//	FootOffDataObject->ExitFootOffState(BoneName);
//}
