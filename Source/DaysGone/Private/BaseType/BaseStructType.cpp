#include "BaseType/BaseStructType.h"
#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"

bool FHumanAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;;
}
