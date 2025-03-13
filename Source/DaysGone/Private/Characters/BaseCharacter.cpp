// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// 틱관련 기능 비활성화
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	//VFX 지상 데칼 투영 영향을 줌
	GetMesh()->bReceivesDecals = false;

	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("BaseAbilitySystemComponent"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributeSet"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetBaseAbilitySystemComponent();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (BaseAbilitySystemComponent)
	{
		//AbilitySystemComponent에 접근 어빌리티 정보 초기값 부여
		BaseAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	//첫번째 인자값이 false면 디버그 모드에선 중단점이 발생하며, 게임에서 로그도 발생
	ensureMsgf(!StartupData.IsNull(), TEXT("Forgot to assigned startup data to %s"), *GetName());
}

UPawnCombatComponent* ABaseCharacter::GetPawnCombatComponent() const
{
	//부모 클래스에선 재구현 하지 않음 자식에서 구현
	return nullptr;
}

UActorUIComponent* ABaseCharacter::GetActorUIComponent() const
{
	//부모 클래스에선 재구현 하지 않음 자식에서 구현
	return nullptr;
}

UPlayerUIComponent* ABaseCharacter::GetPlayerUIComponent() const
{
	return nullptr;
}

UEnemyUIComponent* ABaseCharacter::GetEnemyUIComponent() const
{
	return nullptr;
}
