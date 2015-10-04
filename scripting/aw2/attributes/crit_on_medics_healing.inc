#define ATTRIBUTE_CRIT_ON_MEDICS_HEALING         1075

public Action:Attribute_1075_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_CRIT_ON_MEDICS_HEALING)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!IsValidClient(GetHealTarget(iVictim))) return Plugin_Continue;
    
    iDamageType = MakeCritDamageType(iDamageType);
    
    return Plugin_Changed;
}