// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupDeacon.h"
#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseType/BaseStructType.h"

void UDataAsset_StartupDeacon::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(ASC, Level);

	for(const FHumanAbilitySet& AbilitySet : PlayerStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;
        
		FGameplayAbilitySpec Spec(AbilitySet.AbilityToGrant);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;

		Spec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		ASC->GiveAbility(Spec);
	}
}
