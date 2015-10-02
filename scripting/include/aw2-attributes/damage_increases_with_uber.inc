#define ATTRIBUTE_DAMAGE_INCREASES_WITH_UBER        1064

public Action:Attribute_1064_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DAMAGE_INCREASES_WITH_UBER)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fUber = TF2_GetPlayerUberLevel(iAttacker) / 100.0;
    new Float:fValue = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DAMAGE_INCREASES_WITH_UBER);
    new Float:fDifference = fValue - 1.0;
    fDifference *= fUber;
    fValue = fDifference + 1.0;
    //PrintToChatAll("Damage %.1f -> %.1f (%.2f)", fDamage, fDamage * fValue, fValue);
    fDamage *= fValue;
    AttachParticle(iVictim, PARTICLE_IMPACT_BLUE, 1.25);
    
    return Plugin_Changed;
}