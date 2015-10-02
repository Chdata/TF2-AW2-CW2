#define ATTRIBUTE_BLEED_ON_MAJOR_HIT            1112

public Action:Attribute_1112_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_BLEED_ON_MAJOR_HIT)) return Plugin_Continue;
    if (fDamage <= 50.0) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    TF2_AddCondition(iVictim, TFCond_Bleeding, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_BLEED_ON_MAJOR_HIT));
    
    return Plugin_Continue;
}