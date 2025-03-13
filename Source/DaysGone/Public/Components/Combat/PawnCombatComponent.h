// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AMeleeWeaponBase;



UCLASS()
class DAYSGONE_API UPawnCombatComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	
	//HitDetection
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnHitScanTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);
	
protected:
	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag, AMeleeWeaponBase*> CharacterCarriedWeaponMap;

};
