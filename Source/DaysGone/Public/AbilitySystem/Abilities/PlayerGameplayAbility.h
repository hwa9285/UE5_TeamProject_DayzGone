// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "PlayerGameplayAbility.generated.h"

class APlayerCharacter;
class ADeaconController;
class UHumanCombatComponent;

/**
 * 
 */
UCLASS()
class DAYSGONE_API UPlayerGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	APlayerCharacter* GetPlayerCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Ability")
	ADeaconController* GetDeaconControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	UHumanCombatComponent* GetHumanCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float WeaponBaseDamage, FGameplayTag AttackTypeTag);

	UFUNCTION(BlueprintCallable, Category = "RemoveTag")
	void ClearLooseGamePlayTag(FGameplayTag Tag);
	
private:
	//영웅케릭터의 정보를 가지고 있다면 캐시 TWeakObjectPtr는 공유 참조가 존재하지 않을 때 객체를 자동으로 해제합니다. (약한 포인터)
	TWeakObjectPtr<APlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<ADeaconController> CachedDeaconController;
};
