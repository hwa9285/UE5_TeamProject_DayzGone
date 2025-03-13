// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HumanWeaponBase.h"


AHumanWeaponBase::AHumanWeaponBase()
{
	ItemType = EItemType::Weapon;
}

void AHumanWeaponBase::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles)
{
	GrantedAbilitySpecHandles = SpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AHumanWeaponBase::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}

void AHumanWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AHumanWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
