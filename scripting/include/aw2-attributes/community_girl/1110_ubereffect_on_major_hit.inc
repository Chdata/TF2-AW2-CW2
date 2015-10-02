#define ATTRIBUTE_UBER_ON_MAJOR_HIT         1110

public Action:Attribute_1110_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_UBER_ON_MAJOR_HIT)) return Plugin_Continue;
    if (fDamage <= 60.0) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    TF2_AddCondition(iAttacker, TFCond_Ubercharged, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_UBER_ON_MAJOR_HIT));
    
    return Plugin_Continue;
}