#define ATTRIBUTE_FORCED_FALLOFF_PROJ      1173

public Action:Attribute_1173_OnTakeDamage_Projectile(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding, iProjectile)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;    
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_FORCED_FALLOFF_PROJ)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;

        decl Float:fVelocity[3];
        GetEntPropVector(iProjectile, Prop_Data, "m_vecAbsVelocity", fVelocity);
        new Float:fLength = GetVectorLength(fVelocity);
        
        new Float:fBaseDamage1170 = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_FORCED_FALLOFF_PROJ);
        if (fLength > 1024.0) {
        fLength = 1024.0;
        }
        fLength *= GetRandomFloat(0.85, 1.15);				//15% randomness
        fLength *= -0.0009765625;
        fLength += 1.5;	
        fDamage = fBaseDamage1170;								//Change damage
        fDamage *= fLength;									//Multiply base damage by rampup/falloff    
        return Plugin_Changed;
}