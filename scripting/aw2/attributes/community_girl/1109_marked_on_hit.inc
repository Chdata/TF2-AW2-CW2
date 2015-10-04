#define ATTRIBUTE_MARKED_ON_HIT         1109

public Action:Attribute_1109_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_MARKED_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 6.0) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    TF2_AddCondition(iVictim, TFCond_MarkedForDeath, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_MARKED_ON_HIT));
    
    return Plugin_Continue;
}