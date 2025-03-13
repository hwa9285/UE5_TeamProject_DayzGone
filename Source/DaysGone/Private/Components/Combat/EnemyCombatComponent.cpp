// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "BaseGamePlayTags.h"
#include "Items/Weapon/WeaponBase.h"
#include "Components/BoxComponent.h"
#include "Items/Weapon/MeleeWeaponBase.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	//TODO:: Implement Block Check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = false;
	const bool bIsAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsAttackUnblockable)
	{
		//TODO:: Check if the block is valid

	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		//TODO::Handle Successful Block
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Shared_Event_MeleeHit, EventData);
	}
	
}

void UEnemyCombatComponent::ToggleWeaponCollision(bool bUse)
{
	for (AWeaponBase* Weapon : Weapons)
	{
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

void UEnemyCombatComponent::SetWeapons(AWeaponBase* Weapon)
{
	Weapons.AddUnique(Weapon);

	Weapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	Weapon->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);
}








