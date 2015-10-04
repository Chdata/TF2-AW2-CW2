#define ATTRIBUTE_FORCED_FALLOFF      1171

public Action:Attribute_1171_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;    
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_FORCED_FALLOFF)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;

	new Float:fDistance;
	decl Float:vClientPos[3];
	GetClientAbsOrigin(iAttacker, vClientPos);
	decl Float:vVictimPos[3];
	GetClientAbsOrigin(iVictim, vVictimPos);
	fDistance = GetVectorDistance(vVictimPos, vClientPos);
	new Float:fBaseDamage1170 = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_FORCED_FALLOFF);
	new Float:fFalloffScale1170 = -0.0009765625;
	if (fBaseDamage1170 >= 1000.0)
		{
		fBaseDamage1170 -= 1000.0;
		fFalloffScale1170 = -0.001171875;
		}
	if (fBaseDamage1170 >= 2000.0)
		{
		fBaseDamage1170 -= 1000.0;
		fFalloffScale1170 = -0.0013671875;
		}
	if fDistance > 1024.0 *then fDistance = 1024.0;			//Maximum distance cap
	fDistance *= GetRandomFloat(0.85, 1.15);				//15% randomness
	fDistance *= fFalloffScale1170;
	fDistance += 1.5;	
	fDamage = fBaseDamage1170;								//Change damage
	fDamage *= fDistance;									//Multiply base damage by rampup/falloff    
	return Plugin_Changed;
}