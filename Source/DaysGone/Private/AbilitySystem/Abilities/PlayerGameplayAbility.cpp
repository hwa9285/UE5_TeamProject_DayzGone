// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"
#include "Characters/PlayerCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGamePlayTags.h"
#include "Controllers/DeaconController.h"

#include "BaseDebugHelper.h"

APlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

ADeaconController* UPlayerGameplayAbility::GetDeaconControllerFromActorInfo()
{
	if (!CachedDeaconController.IsValid())
	{
		CachedDeaconController = Cast<ADeaconController>(CurrentActorInfo->PlayerController);
	}

	return CachedDeaconController.IsValid() ? CachedDeaconController.Get() : nullptr;
}

UHumanCombatComponent* UPlayerGameplayAbility::GetHumanCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
	float WeaponBaseDamage, FGameplayTag AttackTypeTag)
{
	check(Effect);

	//ContextHandle을 만들어서 타겟 정보 주입
	FGameplayEffectContextHandle ContextHandle;
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	//SpecHandle을 만들어서 ContextHandle에 정보 주입
	FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

	SpecHandle.Data->SetSetByCallerMagnitude(BaseGamePlayTags::Shared_SetByCaller_BaseDamage, WeaponBaseDamage);

	if (AttackTypeTag.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(AttackTypeTag, WeaponBaseDamage);
	}

	return SpecHandle;
}

void UPlayerGameplayAbility::ClearLooseGamePlayTag(FGameplayTag Tag)
{
	
}
