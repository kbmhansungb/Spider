// Fill out your copyright notice in the Description page of Project Settings.

#include "FootOffData.h"
#include "Animation/AnimInstance.h"

bool UFootOffDataObject::IsFootOffState(const FName& StateName) const
{
	const FFootOffData* FootOffDataPtr = FootOffDataMap.Find(StateName);

	if (!FootOffDataPtr)
	{
		return false;
	}

	return FootOffDataPtr->IsFootOff();
}

void UFootOffDataObject::EnterFootOffState(const FName& StateName)
{
	FootOffDataMap.FindOrAdd(StateName).NumOfEnteredFootOffStates += 1;
}

void UFootOffDataObject::EnterFootOffStates(const TArray<FName>& StateNames)
{
	for (const auto& StateName : StateNames)
	{
		EnterFootOffState(StateName);
	}
}

void UFootOffDataObject::ExitFootOffState(const FName& StateName)
{
	FootOffDataMap.FindOrAdd(StateName).NumOfEnteredFootOffStates -= 1;
}

void UFootOffDataObject::ExitFootOffStates(const TArray<FName>& StateNames)
{
	for (const auto& StateName : StateNames)
	{
		ExitFootOffState(StateName);
	}
}
