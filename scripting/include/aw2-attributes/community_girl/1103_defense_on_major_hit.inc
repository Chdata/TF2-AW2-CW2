#define ATTRIBUTE_DEFENSE_ON_MAJOR_HIT         1103

public Action:Attribute_1103_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DEFENSE_ON_MAJOR_HIT)) return Plugin_Continue;
    if (fDamage <= 30.0) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    TF2_AddCondition(iAttacker, TFCond_DefenseBuffed, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DEFENSE_ON_MAJOR_HIT));
    
    return Plugin_Continue;
}