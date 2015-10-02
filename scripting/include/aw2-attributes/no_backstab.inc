#define ATTRIBUTE_NO_BACKSTAB         1088

// nothing!

public Action:Attribute_1088_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_NO_BACKSTAB)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (iDamageType == TF_DMG_MELEE_CRIT)
    {
        iDamageType = TF_DMG_MELEE;
        fDamage /= 40.0;
        return Plugin_Changed;
    }
    
    return Plugin_Continue;
}