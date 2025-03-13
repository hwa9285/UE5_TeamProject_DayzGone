// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "BaseAbilitySystemComponent.generated.h"

struct FPlayerAbilitySet;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);
	
	UFUNCTION(BlueprintCallable, Category="Ability", meta=(Level="1"))
	void GrantPlayerWeaponAbilities(const TArray<FHumanAbilitySet>& WeaponAbilities, int32 Level, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& SpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool TryActivateAbilityByTag(FGameplayTag Tag);
};
