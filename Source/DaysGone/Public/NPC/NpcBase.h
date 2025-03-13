// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseStructType.h"
#include "GameFramework/Character.h"
#include "NpcBase.generated.h"

UCLASS()
class DAYSGONE_API ANpcBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="NPC")
	FQuestData QuestData;
	
protected:
	
	UPROPERTY(VisibleAnywhere,Blueprintable,Category="Npc")
	USkeletalMeshComponent* SkeletalMesh;
	
};
