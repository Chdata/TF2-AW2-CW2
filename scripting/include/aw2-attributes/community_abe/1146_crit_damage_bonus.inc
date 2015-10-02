#define ATTRIBUTE_CRIT_DAMAGE_BONUS      1146

// I wub you, girl. :3

public Action:Attribute_1146_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_CRIT_DAMAGE_BONUS)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (IsDamageTypeCrit(iDamageType)) 
    {
    fDamage *= GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_CRIT_DAMAGE_BONUS);
    }
    
    return Plugin_Changed;
}