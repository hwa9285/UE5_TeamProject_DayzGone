// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BaseAnimInstance.h"
#include "LinkedAnimLayer.generated.h"

class UHumanAnimInstance;
class UDeaconAnimInstance;
class UFreackerAnimInstance;
/**
 * 
 */
UCLASS()
class DAYSGONE_API ULinkedAnimLayer : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	// UFUNCTION(BlueprintPure, meta= (BlueprintThreadSafe))
	UFUNCTION(BlueprintPure)
	UHumanAnimInstance* GetHumanAnimInstance() const;
	
	// UFUNCTION(BlueprintPure, meta= (BlueprintThreadSafe))
	UFUNCTION(BlueprintPure)
	UDeaconAnimInstance* GetDeaconAnimInstance() const;
	
	// UFUNCTION(BlueprintPure, meta= (BlueprintThreadSafe))
	UFUNCTION(BlueprintPure)
	UFreackerAnimInstance* GetFreackerAnimInstance() const;

};
