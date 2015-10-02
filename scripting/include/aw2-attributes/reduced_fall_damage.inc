#define ATTRIBUTE_REDUCED_FALL_DAMAGE           1066

public Action:Attribute_1066_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    
    new iSlotVictim = GetClientSlot(iVictim);
    if (!ClientHasAttribute(iVictim, iSlotVictim, ATTRIBUTE_REDUCED_FALL_DAMAGE)) return Plugin_Continue;
    
    new iDmgType = iDamageType;
    #if defined ENABLE_SDKHOOKS
    if (iDmgType != DMG_FALL && iDmgType != DMG_CRUSH) return Plugin_Continue;
    #endif
    if (iAttacker != iVictim && IsValidClient(iAttacker)) return Plugin_Continue;

    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fValue = GetClientAttribute(iVictim, iSlotVictim, ATTRIBUTE_REDUCED_FALL_DAMAGE);
    fDamage *= fValue;
    
    return Plugin_Changed;
}