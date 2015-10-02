#define ATTRIBUTE_MELEE_DAMAGE_BONUS	1204

public Action:Attribute_1204_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	//if (iAttacker == iVictim) return Plugin_Continue;
	if (!ClientHasAttribute(iAttacker, _, ATTRIBUTE_MELEE_DAMAGE_BONUS)) return Plugin_Continue;
	if (iSlot != 2) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	
	fDamage *= GetClientAttribute(iAttacker, _, ATTRIBUTE_MELEE_DAMAGE_BONUS);
	
	return Plugin_Changed;
}