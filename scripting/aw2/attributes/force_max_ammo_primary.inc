#define ATTRIBUTE_FORCE_MAX_AMMO_PRIMARY    1060

Attribute_1060_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FORCE_MAX_AMMO_PRIMARY)) return;
    
    new iAmmo = RoundFloat(GetClientAttribute(iClient, iSlot, ATTRIBUTE_FORCE_MAX_AMMO_PRIMARY));
    SetWeaponAmmo(iClient, iSlot, iAmmo);
}