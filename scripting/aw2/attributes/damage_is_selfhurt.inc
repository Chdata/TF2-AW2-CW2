#define ATTRIBUTE_DAMAGE_DONE_IS_SELFHURT      1073

public Action:Attribute_1073_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DAMAGE_DONE_IS_SELFHURT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fSelfHurt = fDamage * GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DAMAGE_DONE_IS_SELFHURT);
    new iSelfHurt = RoundFloat(fSelfHurt);

    new iHealth = GetClientHealth(iAttacker);
    if (iHealth > iSelfHurt) SetEntityHealth(iAttacker, iHealth - iSelfHurt);
    else DealDamage(iAttacker, iSelfHurt);
    
    return Plugin_Continue;
}