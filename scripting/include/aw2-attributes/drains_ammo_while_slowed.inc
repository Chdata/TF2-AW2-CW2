#define ATTRIBUTE_DRAINS_AMMO_WHILE_SLOWED         1013

new g_iDrainAmmoTime[MAXPLAYERS+1] = 0;

Attribute_1013_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DRAINS_AMMO_WHILE_SLOWED)) return iButtons;
    if (!TF2_IsPlayerInCondition(iClient, TFCond_Slowed)) return iButtons;
    
    new iAdd = RoundFloat(GetClientAttribute(iClient, iSlot, ATTRIBUTE_NEW_SLOWED_MOVESPEED));
    
    g_iDrainAmmoTime[iClient] += iAdd;
    
    if (g_iDrainAmmoTime[iClient] >= 50)
    {
        g_iDrainAmmoTime[iClient] -= 50;
        SubtractWeaponAmmo(iClient, iSlot, 1);
    }
    
    return iButtons;
}