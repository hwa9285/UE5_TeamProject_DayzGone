// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"

UBaseAbilitySystemComponent* UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);
	
	return CastChecked<UBaseAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UBaseFunctionLibrary::AddPlaygameTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->AddLooseGameplayTag(Tag);
	}
}

void UBaseFunctionLibrary::RemovePlaygameTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	if (ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->RemoveLooseGameplayTag(Tag);
	}
}

bool UBaseFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	UBaseAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	return ASC->HasMatchingGameplayTag(Tag);
}

bool UBaseFunctionLibrary::IsTargetPawnHostile(APawn* OwningPawn, APawn* TargetPawn)
{
	check(OwningPawn && TargetPawn);

	IGenericTeamAgentInterface* OwningTeamAgent = Cast<IGenericTeamAgentInterface>(OwningPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (OwningTeamAgent && TargetTeamAgent)
	{
		bool Result =  OwningTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
		UE_LOG(LogTemp, Log, TEXT("Diff TeamID %s"), Result? TEXT("true"): TEXT("false"));
		return Result;
	}

	return false;
}

void UBaseFunctionLibrary::BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType)
{
	OutType = NativeActorHasTag(Actor, Tag) ? EBaseConfirmType::Yes : EBaseConfirmType::No;
}

UPawnCombatComponent* UBaseFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* Actor)
{
	check(Actor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(Actor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UBaseFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* Actor,
	EBaseValidType& OutValidType)
{
	UPawnCombatComponent* HumanComponent = NativeGetPawnCombatComponentFromActor(Actor);
	OutValidType = HumanComponent ? EBaseValidType::Valid : EBaseValidType::Invalid;
	return HumanComponent;
}