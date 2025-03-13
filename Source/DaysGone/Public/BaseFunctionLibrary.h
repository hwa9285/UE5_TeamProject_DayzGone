// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseType/BaseEnumType.h"
#include "BaseFunctionLibrary.generated.h"

class UBaseAbilitySystemComponent;
class UPawnCombatComponent;
/**
 * 
 */
UCLASS()
class DAYSGONE_API UBaseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UBaseAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AddPlaygameTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void RemovePlaygameTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* OwningPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta=(Display="Does Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta=(Display="Get PawnCombatComponent From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* Actor, EBaseValidType& OutValidType);
};
