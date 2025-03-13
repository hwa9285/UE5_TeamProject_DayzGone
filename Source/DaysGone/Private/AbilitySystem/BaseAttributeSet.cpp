// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "BaseDebugHelper.h"
#include "BaseGamePlayTags.h"
#include "Components/Widget/PlayerUIComponent.h"
#include "Components/Widget/ActorUIComponent.h"
#include "Interfaces/PawnUIInterface.h"
#include "BaseFunctionLibrary.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitCurrentHP(1.f);
	InitMaxHP(1.f);
	InitDefence(1.f);
	InitAttack(1.f);
	InitDamageTaken(1.f);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	UActorUIComponent* PawnUIComponent = CachedUIInterface->GetActorUIComponent();
	
	if (Data.EvaluatedData.Attribute == GetCurrentHPAttribute())
	{
		const float NewCurrentHp = FMath::Clamp(GetCurrentHP(), 0.0f, GetMaxHP());
		SetCurrentHP(NewCurrentHp);

		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHP() / GetMaxHP());
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeHp = GetCurrentHP();
		const float Damage = GetDamageTaken();

		const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.0f, GetMaxHP());

		SetCurrentHP(NewCurrentHp);

		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHP() / GetMaxHP());
		
		const FString DebugString = FString::Printf(TEXT("Before Hp: &f, Damage: %f, NewCurrentHp: %f"), BeforeHp, Damage, NewCurrentHp);
		// Debug::Print(DebugString, FColor::Green);

		// Character Death Process
		if (NewCurrentHp == 0.0f)
		{
			// Character Death Process
			UBaseFunctionLibrary::AddPlaygameTagToActor(Data.Target.GetAvatarActor(), BaseGamePlayTags::Shared_Status_Dead);
		}
	}
}
