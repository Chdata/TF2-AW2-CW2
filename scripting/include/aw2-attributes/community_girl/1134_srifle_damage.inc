// The Srifle is not effected by the normal damage reduction attribute; only fDamage can reduce its damage. This attribute's only purpose is to be used with Srifles, or other future weapons that might not be effected by Valve +/- damage done attributes (such as the short circuit)...

#define ATTRIBUTE_SRIFLE_DAMAGE      1134

public Action:Attribute_1134_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_SRIFLE_DAMAGE)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    fDamage *= GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_SRIFLE_DAMAGE);
	
    return Plugin_Changed;
}