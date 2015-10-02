#define ATTRIBUTE_CRIT_DAMAGE_REDUC      1147

// Girl x Abe

public Action:Attribute_1147_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_CRIT_DAMAGE_REDUC)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (IsDamageTypeCrit(iDamageType)) {
    fDamage *= GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_CRIT_DAMAGE_REDUC);
    }
    
    return Plugin_Changed;
}