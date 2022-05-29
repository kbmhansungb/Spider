// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Animation/AnimInstance.h"
#include "SpiderMonster.generated.h"

UCLASS()
class SPIDERMODULE_API ASpiderMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpiderMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;
};

UCLASS()
class SPIDERMODULE_API USpiderAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
};
