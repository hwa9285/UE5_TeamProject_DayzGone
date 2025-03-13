#pragma once

UENUM()
enum class EBaseConfirmType : uint8
{
	Yes,
	No,
};

UENUM()
enum class EBaseValidType : uint8
{
	Valid,
	Invalid,
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Supplies,
	Ingredients,
	Ammo
};

UENUM()
enum class EBaseSuccessType : uint8
{
	Success,
	Failed,
};

UENUM()
enum class EWeaponType: uint8
{
	Range,
	Melee
};

UENUM()
enum class ESuppliesType: uint8
{
	Recovery,
	Throw
};

UENUM(Blueprintable)
enum class EAmmoType: uint8
{
	Rifle,
	AssaultRifle,
	Shotgun,
	Pistol,
	Bolt,
	RPG,
	Special,
	None
};

UENUM(BlueprintType)
enum class EEquipType: uint8
{
	Primary,
	Secondary,
	Special,
	Melee
};