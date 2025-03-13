// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "ActorUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangeDelegate, float, NewPercent);

/**
 * 
 */
UCLASS()
class DAYSGONE_API UActorUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentHpChanged;
};
