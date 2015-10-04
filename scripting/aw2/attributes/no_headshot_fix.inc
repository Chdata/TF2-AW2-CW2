#define ATTRIBUTE_NO_HEADSHOT         42

public Action:Attribute_42_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_NO_HEADSHOT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (iDamageType == TF_DMG_RIFLE_CRIT) iDamageType = TF_DMG_RIFLE_CHARGED;
    
    return Plugin_Changed;
}