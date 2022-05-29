// Fill out your copyright notice in the Description page of Project Settings.

#include "TeuthisanAnimBlueprint.h"

UTheuthisanAnimBlueprint::UTheuthisanAnimBlueprint()
	: FootOfDataObject(nullptr)
{
}

//void UTheuthisanAnimBlueprint::NativeInitializeAnimation()
//{
//	FootOfDataObject = NewObject<UFootOffDataObject>(this, FName("FootOfDataObject"));
//}

UFootOffDataObject* UTheuthisanAnimBlueprint::GetFootOfDataObject_Implementation()
{
	if (!FootOfDataObject)
	{
		FootOfDataObject = NewObject<UFootOffDataObject>(this, FName("FootOfDataObject"));
	}

	return FootOfDataObject;
}
