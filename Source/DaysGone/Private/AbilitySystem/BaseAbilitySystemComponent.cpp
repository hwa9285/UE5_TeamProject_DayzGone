// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"

#include "BaseGamePlayTags.h"
#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"
#include "BaseType/BaseStructType.h"

void UBaseAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	//������ �������� �Է� ����
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		TryActivateAbility(Spec.Handle);
	}
}

void UBaseAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid() || !InputTag.MatchesTag(BaseGamePlayTags::InputTag_Hold))
	{
		return;
	}

	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag) && Spec.IsActive())
		{
			CancelAbilityHandle(Spec.Handle);
		}
	}
}

void UBaseAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FHumanAbilitySet>& WeaponAbilities,
	int32 Level, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (WeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FHumanAbilitySet& WeaponAbilitySet : WeaponAbilities)
	{
		if (!WeaponAbilitySet.IsValid()) continue;

		FGameplayAbilitySpec Spec(WeaponAbilitySet.AbilityToGrant);
		Spec.SourceObject = GetAvatarActor();
		Spec.Level = Level;
		Spec.DynamicAbilityTags.AddTag(WeaponAbilitySet.InputTag);
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(Spec));
        
	}
}

void UBaseAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& SpecHandlesToRemove)
{
	if (SpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	SpecHandlesToRemove.Empty();
}

bool UBaseAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag Tag)
{
	check(Tag.IsValid());

	TArray<FGameplayAbilitySpec*> AbilitySpecs;

	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

	if (!AbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

		check(AbilitySpec);

		if (!AbilitySpec->IsActive())
		{
			return TryActivateAbility(AbilitySpec->Handle);
		}
	}
	return false;
}
