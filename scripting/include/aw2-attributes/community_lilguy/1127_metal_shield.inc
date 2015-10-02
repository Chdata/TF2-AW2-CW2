#define ATTRIBUTE_METAL_SHIELD	1127

public Action:Attribute_1127_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iVictim)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (!ClientHasAttribute(iVictim, _, ATTRIBUTE_METAL_SHIELD)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;

	//Get metal and check for at least 1
	new iMetal = GetEntData(iVictim, FindDataMapOffs(iVictim, "m_iAmmo") + (3 * 4));
	if (iMetal <= 0) return Plugin_Continue;

	//Ignore if fall damage
	#if defined ENABLE_SDKHOOKS
	if (iDamageType & DMG_FALL == DMG_FALL || iDamageType & DMG_CRUSH == DMG_CRUSH) return Plugin_Continue; //Fall
	#endif

	//If damage is headshot or backstab
	if (iDamageType == TF_DMG_RIFLE_CRIT) return Plugin_Continue;
	if ((iDamageType == TF_DMG_MELEE_CRIT) && (GetPlayerClass(iAttacker) == CLASS_SPY) && (fDamage > (4.0 * float(GetClientMaxHealth(iVictim))))) return Plugin_Continue;
	//POWER OVERWHELMING
	if (fDamage >= float(iMetal + GetClientHealth(iVictim))) return Plugin_Continue;

	//Get attribute value (Percentage)
	new Float:fMulti = GetClientAttribute(iVictim, _, ATTRIBUTE_METAL_SHIELD);

	//Metal lost is attribute value
	new Float:fMetal = fDamage * fMulti * -1.0;
	new iDmgMetal = RoundFloat(fMetal);

	//New damage taken is rest of damage not taken by metal
	fDamage *= (1.0 - fMulti);
    
	//Deal excess damage if not enough metal
	if (iDmgMetal > iMetal) {
		fDamage += (iDmgMetal - iMetal);
	}

	//Check if player has metal return attribute
	if (ClientHasAttribute(iAttacker, iSlot, 299) && ClientHasAttribute(iAttacker, iSlot, 301) && (GetPlayerClass(iAttacker) == CLASS_ENGINEER)) {
		GiveEngineerMetal(iAttacker, iDmgMetal);
	}
	
	//Take away metal
	GiveEngineerMetal(iVictim, iDmgMetal);
	//If all metal gone, play sound
	iMetal = GetEntData(iVictim, FindDataMapOffs(iVictim, "m_iAmmo") + (3 * 4));
	if (iMetal == 0) {
		EmitSoundToClient(iVictim, SOUND_SAPPER_BREAK);
	}
	//particles from girl with <3, let's hope they look pretty
	if (iMetal != 0) {
		AttachParticle(iVictim, PARTICLE_METAL_SHIELD_SPARKS1, 0.5);
		AttachParticle(iVictim, PARTICLE_METAL_SHIELD_SPARKS2, 0.5);
	}

	return Plugin_Changed;
}
