// Fill out your copyright notice in the Description page of Project Settings.

#include "TeuthisanAnimBlueprint.h"

UTheuthisanAnimBlueprint::UTheuthisanAnimBlueprint()
{
	FootOfDataObject = NewObject<UFootOffDataObject>(GetOuter(), FName("FootOfDataObject"));
}

UFootOffDataObject* UTheuthisanAnimBlueprint::GetFootOfDataObject_Implementation()
{
	return FootOfDataObject;
}
