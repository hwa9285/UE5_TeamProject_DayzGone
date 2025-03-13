// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UEnemyUIComponent;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class DAYSGONE_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SectionID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32  SaveID;


protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual UActorUIComponent* GetActorUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

private:
	void InitEnemyStartUpData();
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "UI", meta = (AllowPrivateAccess = "true"))
	UEnemyUIComponent* EnemyUIComponent;
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
	UEnemyCombatComponent* EnemyCombatComponent;
};

