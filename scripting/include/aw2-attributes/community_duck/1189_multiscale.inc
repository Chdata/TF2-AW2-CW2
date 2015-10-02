#define ATTRIBUTE_MULTISCALE        1189

//This attribute causes the user to take 50% less damage as long as they have full health or more. You should probably slap -x% health from healers on a weapon that uses this (to stop overheal abuse.)
//WARNING: Remember to think about weapons that increase the player's max health during their life like the dalokohs bar. They will be extremely useful in combination with this.

//If you get the reference you deserve an internet cookie.

new Float:g_fmaxhealth[MAXPLAYERS+1] = 0.0;

Attribute_1189_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MULTISCALE)) return;
    g_fmaxhealth[iClient] = Float:GetClientHealth(iClient);
}

public Action:Attribute_1189_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iVictim, 0, ATTRIBUTE_MULTISCALE)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (GetClientHealth(iVictim) >= g_fmaxhealth[iVictim]) return Plugin_Continue;
	
    fDamage = fDamage * GetClientAttribute(iVictim, iSlot, ATTRIBUTE_MULTISCALE);
    return Plugin_Changed;
}
