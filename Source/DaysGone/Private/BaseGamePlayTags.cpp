#include "BaseGamePlayTags.h"

namespace BaseGamePlayTags
{
	//Input Tags
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip1, "InputTag.Equip1")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip2, "InputTag.Equip2")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip3, "InputTag.Equip3")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip4, "InputTag.Equip4")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip1, "InputTag.UnEquip1")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip2, "InputTag.UnEquip2")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip3, "InputTag.UnEquip3")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip4, "InputTag.UnEquip4")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_PickUpWeapon, "InputTag.PickUpWeapon")
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Heal, "InputTag.Heal")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Inventory, "InputTag.Inventory")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Reload, "InputTag.Reload")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Shot, "InputTag.Shot")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MeleeAttack, "InputTag.MeleeAttack")
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Hold, "InputTag.Hold")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Hold_Sprint, "InputTag.Hold.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Hold_Interact, "InputTag.Hold.Interact")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Hold_Zoom, "InputTag.Hold.Zoom")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Hold_AutoShot, "InputTag.Hold.AutoShot")

	
	
    //Player Tags
    UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Melee, "Player.SetByCaller.AttackType.Melee")
    UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Ranged, "Player.SetByCaller.AttackType.Ranged")

    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip1, "Player.Ability.Equip1")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip2, "Player.Ability.Equip2")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip3, "Player.Ability.Equip3")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip4, "Player.Ability.Equip4")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip1, "Player.Ability.Unequip1")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip2, "Player.Ability.Unequip2")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip3, "Player.Ability.Unequip3")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip4, "Player.Ability.Unequip4")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause")
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Heal, "Player.Ability.Heal")
	
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SpawnWeapons, "Player.Ability.SpawnWeapons")
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Sprint, "Player.Ability.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Interact, "Player.Ability.Interact")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PickWeapon, "Player.Ability.PickWeapon")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Zoom, "Player.Ability.Zoom")
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Reload, "Player.Ability.Reload")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Shot, "Player.Ability.Shot")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_AutoShot, "Player.Ability.AutoShot")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_MeleeAttack, "Player.Ability.MeleeAttack")

    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equip1, "Player.Event.Weapon.Equip1")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equip2, "Player.Event.Weapon.Equip2")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equip3, "Player.Event.Weapon.Equip3")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_Equip4, "Player.Event.Weapon.Equip4")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_UnEquip1, "Player.Event.Weapon.UnEquip1")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_UnEquip2, "Player.Event.Weapon.UnEquip2")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_UnEquip3, "Player.Event.Weapon.UnEquip3")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Weapon_UnEquip4, "Player.Event.Weapon.UnEquip4")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Reload, "Player.Event.Reload")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Shot, "Player.Event.Shot")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_PickWeapon, "Player.Event.PickWeapon")
    UE_DEFINE_GAMEPLAY_TAG(Player_Event_Heal, "Player.Event.Heal")
       
    UE_DEFINE_GAMEPLAY_TAG(Player_Status_FinalAttack, "Player.Status.FinalAttack")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Interacting, "Player.Status.Interacting")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Sprinting, "Player.Status.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Zoom, "Player.Status.Zoom")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Reloading, "Player.Status.Reloading")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Shot, "Player.Status.Shot")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_MeleeAttack, "Player.Status.MeleeAttack")

	// Weapon Tags
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_PrimaryWeapon, "Weapon.Type.PrimaryWeapon")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_PrimaryWeapon_Rifle, "Weapon.Type.PrimaryWeapon.Rifle")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_PrimaryWeapon_AssaultRifle, "Weapon.Type.PrimaryWeapon.AssaultRifle")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_PrimaryWeapon_ShotGun, "Weapon.Type.PrimaryWeapon.ShotGun")
	
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_SpecialWeapon, "Weapon.Type.SpecialWeapon")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_SpecialWeapon_SniperRifle, "Weapon.Type.SpecialWeapon.SniperRifle")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_SpecialWeapon_CrossBow, "Weapon.Type.SpecialWeapon.CrossBow")
	
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_SidearmWeapon, "Weapon.Type.SidearmWeapon")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_SidearmWeapon_Pistol, "Weapon.Type.SidearmWeapon.Pistol")
	
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_MeleeWeapon, "Weapon.Type.MeleeWeapon")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_MeleeWeapon_Axe, "Weapon.Type.MeleeWeapon.Axe")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_MeleeWeapon_Bat, "Weapon.Type.MeleeWeapon.Bat")
    UE_DEFINE_GAMEPLAY_TAG(Weapon_Type_MeleeWeapon_Knife, "Weapon.Type.MeleeWeapon.Knife")
	
	

    // Enemy Tags
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack")
    UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Default, "Enemy.Status.Default")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Sensed, "Enemy.Status.Sensed")
	
    // Shared Tags
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_RangeHit, "Shared.Event.RangeHit")
    UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead")
    UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Respawn, "Shared.Status.Respawn")
}