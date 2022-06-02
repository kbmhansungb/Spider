// Fill out your copyright notice in the Description page of Project Settings.

#include "FootOffData.h"
#include "Animation/AnimInstance.h"

void UFootOffDataObject::UpdateFootOffData(USkeletalMeshComponent* SkeletalMeshComponent)
{
	if (IsValid(SkeletalMeshComponent) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent is not valid."));
		return;
	}

	const FTransform& ComponentToWorld = SkeletalMeshComponent->GetComponentToWorld();

	for (auto& Pair : FootOffDataMap)
	{
		const FName& Name = Pair.Key;
		FFootOffData& FootOffData = Pair.Value;

		//if (FootOffData.IsFootOff())
		{
			FootOffData.BonePosition_WorldSpace = ComponentToWorld.TransformPosition(FootOffData.BonePosition_ComponentSpace);
		}

		// Start trace
		FVector Start = FootOffData.BonePosition_WorldSpace;
		Start.Z += 30.0f;
		FVector End = FVector(Start.X, Start.Y, Start.Z - 160.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SkeletalMeshComponent->GetOwner());
		FootOffData.IsHit = SkeletalMeshComponent->GetWorld()->LineTraceSingleByChannel(
			FootOffData.HitResult, Start, End, ECollisionChannel::ECC_WorldStatic, Params);

		// Set Traced Position
		FootOffData.TracedPosition_WorldSpace = FootOffData.IsHit ? FootOffData.HitResult.Location : FootOffData.BonePosition_WorldSpace;

		// Set Fixed Position
		FootOffData.FixedPosition_WorldSpace = FootOffData.TracedPosition_WorldSpace;
		if (FootOffData.BonePosition_ComponentSpace.Z > 0.0f)
		{
			FootOffData.FixedPosition_WorldSpace.Z += FootOffData.BonePosition_ComponentSpace.Z;
		}

#ifdef WITH_EDITOR 

		// Debug draw
		const FColor& Color = FootOffData.IsHit ? FColor::Green : FColor::Red;
		DrawDebugSphere(SkeletalMeshComponent->GetWorld(), Start, 1.0f, 16, Color);
		DrawDebugDirectionalArrow(SkeletalMeshComponent->GetWorld(), Start, FootOffData.TracedPosition_WorldSpace, 5.0f, Color);

#endif // WITH_EDITOR 
	}
}

void UFootOffDataObject::EnterFootOffState(const FName& BoneName)
{
	FFootOffData* FootOffDataPtr = FootOffDataMap.Find(BoneName);
	if (FootOffDataPtr)
	{
		FootOffDataPtr->NumOfEnteredFootOffStates += 1;
	}
}

void UFootOffDataObject::EnterFootOffStates(const TArray<FName>& BoneNames)
{
	for (const auto& BoneName : BoneNames)
	{
		EnterFootOffState(BoneName);
	}
}

void UFootOffDataObject::ExitFootOffState(const FName& BoneName)
{
	FFootOffData* FootOffDataPtr = FootOffDataMap.Find(BoneName);
	if (FootOffDataPtr)
	{
		FootOffDataPtr->NumOfEnteredFootOffStates -= 1;
	}
}

void UFootOffDataObject::ExitFootOffStates(const TArray<FName>& BoneNames)
{
	for (const auto& BoneName : BoneNames)
	{
		ExitFootOffState(BoneName);
	}
}

void UFootOffDataObject::UpdateFootOffDataFromNotifyState(const FName& BoneName, bool IsUpdateMaxFootOffHeight)
{
	FFootOffData& FootOfData = FootOffDataMap.FindOrAdd(BoneName);
	
	// Todo
	//if (IsUpdateMaxFootOffHeight)
	//{
	//	FootOfData.MaxFootOffHeight = FMath::Max(FootOfData.MaxFootOffHeight, FootOfData.BonePosition_ComponentSpace.Z);
	//}
}
