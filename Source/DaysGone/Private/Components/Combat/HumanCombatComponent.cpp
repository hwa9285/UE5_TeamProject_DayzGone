// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HumanCombatComponent.h"
//#include "Items/Weapon/WeaponBase.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseGamePlayTags.h"
#include "BaseDebugHelper.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Items/HumanWeaponBase.h"
#include "Items/MeleeWeapon.h"

void UHumanCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AHumanWeaponBase* Weapon,
                                                  bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTag), TEXT("%s has already been as carried weapon"), *WeaponTag.ToString()); 
	check(Weapon);

	CharacterCarriedWeaponMap.Emplace(WeaponTag, Weapon);

	
	Weapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	Weapon->OnHitScanTarget.BindUObject(this, &ThisClass::OnHitScanTargetActor);
	Weapon->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTag;
	}
}

void UHumanCombatComponent::UnregisterSpawnedWeapon(AHumanWeaponBase* Weapon)
{
	FGameplayTag WeaponTag = Weapon->WeaponData.WeaponType;
	CharacterCarriedWeaponMap.FindAndRemoveChecked(WeaponTag);
}

AHumanWeaponBase* UHumanCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	if (CharacterCarriedWeaponMap.Contains(WeaponTag))
	{
		if (AHumanWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AHumanWeaponBase* UHumanCombatComponent::GetCharacterCarriedWeaponByEnum(EEquipType WeaponType) const
{
	FGameplayTag WeaponTag;
	if (WeaponType == EEquipType::Primary) WeaponTag = BaseGamePlayTags::Weapon_Type_PrimaryWeapon;
	if (WeaponType == EEquipType::Secondary) WeaponTag = BaseGamePlayTags::Weapon_Type_SidearmWeapon;
	if (WeaponType == EEquipType::Special) WeaponTag = BaseGamePlayTags::Weapon_Type_SpecialWeapon;
	if (WeaponType == EEquipType::Melee) WeaponTag = BaseGamePlayTags::Weapon_Type_MeleeWeapon;
	return GetCharacterCarriedWeaponByTag(WeaponTag);
}

AHumanWeaponBase* UHumanCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UHumanCombatComponent::ToggleWeaponCollision(bool bUse, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AHumanWeaponBase* Weapon = GetCharacterCurrentEquippedWeapon();
		check(Weapon);

		if (bUse)
		{
			Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
}

void UHumanCombatComponent::SpawnWeaponInCharacterBackSocket(TSubclassOf<AHumanWeaponBase> Weapon)
{
	
}

void UHumanCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	
	OverlappedActors.AddUnique(HitActor);
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Shared_Event_MeleeHit, Data);
}

void UHumanCombatComponent::OnHitScanTargetActor(AActor* HitActor)
{
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Shared_Event_RangeHit, Data);
}

void UHumanCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
}
