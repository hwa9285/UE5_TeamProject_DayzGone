// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset_StartupBase.generated.h"

class UBaseGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UDataAsset_StartupBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>> GAS, UBaseAbilitySystemComponent* InASC, int32 Level);

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;
};
