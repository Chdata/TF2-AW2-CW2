#define ATTRIBUTE_DRAINS_UBER_ON_HIT            1065

public Action:Attribute_1065_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DRAINS_UBER_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fUber = TF2_GetPlayerUberLevel(iAttacker);
    fUber += 100.0*GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DRAINS_UBER_ON_HIT);
    TF2_SetPlayerUberLevel(iAttacker, fUber);
    
    return Plugin_Continue;
}