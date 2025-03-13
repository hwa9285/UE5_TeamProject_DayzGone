// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/CharacterAnimInstance.h"
#include "HumanAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAYSGONE_API UHumanAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

protected:
	bool bIsFalling = false;
	bool bIsSprinting = false;
};
