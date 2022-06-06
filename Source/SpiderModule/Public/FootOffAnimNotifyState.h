// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FootOffData.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FootOffAnimNotifyState.generated.h"

/*
 *
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UFootOffInterface : public UInterface
{
	GENERATED_BODY()
};

class IFootOffInterface
{
	GENERATED_BODY()

public:
	/** Add interface function declarations here */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UFootOffDataObject* GetFootOfDataObject();
	virtual UFootOffDataObject* GetFootOfDataObject_Implementation() { return nullptr; };
};

/*
 *
 */
UCLASS(MinimalAPI)
class UFootOffFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = Get)
	static UFootOffDataObject* GetFootOfDataObjectFromSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent);

	//UFUNCTION(BlueprintCallable, Category = Edit)
	//static void EnterAnimNotifyState(UFootOffDataObject* FootOffDataObject, const FName& BoneName);

	//UFUNCTION(BlueprintCallable, Category = Edit)
	//static void ExitAnimNotifyState(UFootOffDataObject* FootOffDataObject, const FName& BoneName);
};

UCLASS(DefaultToInstanced, editinlinenew)
class UFootOffAnimNotifyState final : public UAnimNotifyState
{
	GENERATED_BODY()

//public:
//	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
//	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	//FBoneReference TargetBone;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	FVector BoneOffset_ComponentSpace;
//private:
//#if WITH_EDITOR
//	virtual void OnAnimNotifyCreatedInEditor(FAnimNotifyEvent& ContainingAnimNotifyEvent) override;;
//#endif
//
//	FTransform GetComponentSpaceTransform(const FReferenceSkeleton& RefSkeleton, const UAnimSequence* AnimSequence, int32 TrackIndex, float Time, int32 BoneIndex) const;
};