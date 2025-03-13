// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Execs/GEExecCalc_DamageTaken.h"

#include "BaseDebugHelper.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "BaseGamePlayTags.h"

struct FDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Defence, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, DamageTaken, Target, false);
	}
};

static const FDamageCapture& GetDamageCapture()
{
	static FDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/*
	//������Ƽ ����
	FProperty* AttackProperty = FindFieldChecked<FProperty>(
		UBaseAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Attack)
	);

	//ĸó ����
	FGameplayEffectAttributeCaptureDefinition AttackCaptureDefinition(
		AttackProperty,
		EGameplayEffectAttributeCaptureSource::Source,
		false
	);

	RelevantAttributesToCapture.Add(AttackCaptureDefinition);
	*/

	//Define�� �̿��� ĸó���� ���
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DefenceDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackDef, EvaluateParameters, SourceAttack);

	float BaseDamage = 0.f;


	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BaseGamePlayTags::Shared_SetByCaller_BaseDamage))
		{
			// Debug::Print(TEXT("BaseDamage: "), TagMagnitude.Value);
			BaseDamage = TagMagnitude.Value;
		}
		else if (TagMagnitude.Key.MatchesTagExact(BaseGamePlayTags::Player_SetByCaller_AttackType_Melee))
		{
			// Debug::Print(TEXT("MeleeDamage: "), TagMagnitude.Value);
			BaseDamage = TagMagnitude.Value;
		}
		else if (TagMagnitude.Key.MatchesTagExact(BaseGamePlayTags::Player_SetByCaller_AttackType_Ranged))
		{
			// Debug::Print(TEXT("RangedDamage: "), TagMagnitude.Value);
			BaseDamage = TagMagnitude.Value;
		}
	}

	float TargetDefence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DefenceDef, EvaluateParameters, TargetDefence);
	
	const float FinalDamage = BaseDamage * SourceAttack / TargetDefence;

	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
}
