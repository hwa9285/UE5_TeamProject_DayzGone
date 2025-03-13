// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"

void UDataAsset_StartupBase::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level)
{
	check(ASC);

	GrantAbilities(ActivateOnGivenAbilities, ASC, Level);
	GrantAbilities(ReactiveAbilities, ASC, Level);

	if (!StartupGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& BP_Effect : StartupGameplayEffects)
		{
			if (!BP_Effect) continue;

			UGameplayEffect* EffectCDO = BP_Effect->GetDefaultObject<UGameplayEffect>();
			ASC->ApplyGameplayEffectToSelf(EffectCDO, Level, ASC->MakeEffectContext());
		}
	}
}

void UDataAsset_StartupBase::GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>> GAS,
	UBaseAbilitySystemComponent* InASC, int32 Level)
{
	//�����÷��̾����Ƽ�� ������ Ż��
	if (GAS.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UBaseGameplayAbility> Ability : GAS)
	{
		FGameplayAbilitySpec Spec(Ability);
		Spec.SourceObject = InASC->GetAvatarActor();
		Spec.Level = Level;

		InASC->GiveAbility(Spec);
	}
}
