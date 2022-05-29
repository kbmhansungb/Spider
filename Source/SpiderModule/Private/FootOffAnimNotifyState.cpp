// Fill out your copyright notice in the Description page of Project Settings.

#include "FootOffAnimNotifyState.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "CollisionQueryParams.h"
#include "FootOffData.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animation/AnimInstance.h"

bool UFootOffStateBase::GetBoneHitResult(USkeletalMeshComponent* SkeletalMeshComponent, const FName& BoneName, FHitResult& HItResult, FVector& OriginalPosition)
{
	if (!SkeletalMeshComponent)
	{
		return false;
	}
	FVector Start = OriginalPosition;
	Start.Z += 30.0f;
	FVector End = FVector(Start.X, Start.Y, Start.Z - 60.0f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(SkeletalMeshComponent->GetOwner());
	//Params.AddIgnoredComponent(SkeletalMeshComponent);
	bool IsHit = SkeletalMeshComponent->GetWorld()->LineTraceSingleByChannel(HItResult, Start, End, ECollisionChannel::ECC_WorldStatic, Params);

#ifdef WITH_EDITOR 

	FColor Color = UFootOffStateBase::NotifyColor;
	FColor ColorBurn = FColor(Color.R * 0.5f, Color.G * 0.5f, Color.B * 0.5f, Color.A * 0.5f);
	DrawDebugSphere(SkeletalMeshComponent->GetWorld(), Start, 0.5f, 16, Color);
	
	DrawDebugDirectionalArrow(SkeletalMeshComponent->GetWorld(), Start, IsHit ? HItResult.Location : End, 5.0f, Color);
	if (IsHit)
	{
		DrawDebugSphere(SkeletalMeshComponent->GetWorld(), IsHit ? HItResult.Location : End, 0.5f, 16, ColorBurn);
	}

#endif // WITH_EDITOR 

	return IsHit;
}

void UFootOffStateBase::UpdateBonePosition(USkeletalMeshComponent* SkeletalMeshComponent, const FName& BoneName)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is not valid."));
		return;
	}

	IReactToFeetOffInterface* ReactToFeetOffInterface = Cast<IReactToFeetOffInterface>(AnimInstance);
	if (!ReactToFeetOffInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is not implement ReactToFeetOffInterface."));
		return;
	}

	UFootOffDataObject* DataObject = IReactToFeetOffInterface::Execute_GetFootOfDataObject(AnimInstance);
	if (!DataObject)
	{
		UE_LOG(LogTemp, Error, TEXT("FootOffDataObject is not valid."));
		return;
	}

	FFootOfData& FootOfData = DataObject->FootOfDataMap.FindOrAdd(BoneName);
	FHitResult HitResult;
	bool IsHit = GetBoneHitResult(SkeletalMeshComponent, BoneName, HitResult, FootOfData.OriginalPosition);

	FootOfData.HitPosition = HitResult.Location;
	FootOfData.IsFootOffState = true;
	FootOfData.IsHit = IsHit;
}
