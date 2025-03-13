// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/LinkedAnimLayer.h"

#include "AnimInstances/Freacker/FreackerAnimInstance.h"
#include "AnimInstances/Human/DeaconAnimInstance.h"
#include "AnimInstances/Human/HumanAnimInstance.h"

UHumanAnimInstance* ULinkedAnimLayer::GetHumanAnimInstance() const
{
	return Cast<UHumanAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

UDeaconAnimInstance* ULinkedAnimLayer::GetDeaconAnimInstance() const
{
	return Cast<UDeaconAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

UFreackerAnimInstance* ULinkedAnimLayer::GetFreackerAnimInstance() const
{
	return Cast<UFreackerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
