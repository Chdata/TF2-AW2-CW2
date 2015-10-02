#define ATTRIBUTE_DISARM_ON_VERYMAJOR_HIT         1114

public Action:Attribute_1114_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DISARM_ON_VERYMAJOR_HIT)) return Plugin_Continue;
    if (fDamage <= 85.0) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    TF2_AddCondition(iVictim, TFCond_RestrictToMelee, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DISARM_ON_VERYMAJOR_HIT));
    
    return Plugin_Continue;
}