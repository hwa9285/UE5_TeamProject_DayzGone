// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseType/BaseEnumType.h"
#include "BaseGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EBaseAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

class UPawnCombatComponent;
class UBaseAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EBaseAbilityActivationPolicy AbilityActivationPolicy = EBaseAbilityActivationPolicy::OnTriggered;
	
	UFUNCTION(BlueprintPure, Category = "Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Ability")
	UBaseAbilitySystemComponent* GetBaseAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (Display = "Apply Gameplay Effect Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, EBaseSuccessType& OutSuccessType);

};
