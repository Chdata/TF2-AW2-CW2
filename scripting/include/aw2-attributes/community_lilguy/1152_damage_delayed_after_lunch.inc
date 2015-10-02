#define ATTRIBUTE_DAMAGE_TAKEN_DELAYED_AFTER_LUNCH	1152

new bool:g_bLunched[MAXPLAYERS+1] = false;

Attribute_1152_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!IsValidClient(iClient)) return iButtons;
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DAMAGE_TAKEN_DELAYED_AFTER_LUNCH)) return iButtons;
	//If already delaying damage
	if (g_bLunched[iClient]) return iButtons;
	
	//Works for either Scout or Heavy lunches
	if (TF2_IsPlayerInCondition(iClient, TFCond_Taunting)) g_bLunched[iClient] = true;
	if (TF2_IsPlayerInCondition(iClient, TFCond_Bonked)) TF2_RemoveCondition(iClient, TFCond_Bonked);
	new Float:fExpireTime = GetClientAttribute(iClient, _, ATTRIBUTE_DAMAGE_TAKEN_DELAYED_AFTER_LUNCH);
	CreateTimer(fExpireTime, Attribute_1152_Expire, iClient);
	return iButtons;
}

public Action:Attribute_1152_Expire(Handle:hTimer, any:iClient)
{
	if (g_bLunched[iClient]) g_bLunched[iClient] = false;
}

public Action:Attribute_1152_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iVictim)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (!ClientHasAttribute(iVictim, _, ATTRIBUTE_DAMAGE_TAKEN_DELAYED_AFTER_LUNCH)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;

	if (!g_bLunched[iVictim]) return Plugin_Continue;

	//Ignore if delayed damage
	if (iDamageType & TF_DMG_DELAY == TF_DMG_DELAY) return Plugin_Continue;

	//Ignore if environmental damage
	#if defined ENABLE_SDKHOOKS
	if (iDamageType & DMG_FALL == DMG_FALL || iDamageType & DMG_CRUSH == DMG_CRUSH) return Plugin_Continue; //Fall
	if (iDamageType & DMG_VEHICLE == DMG_VEHICLE) return Plugin_Continue; //Train
	if (iDamageType & DMG_DROWN == DMG_DROWN) return Plugin_Continue; //Drown
	if (iDamageType & DMG_NERVEGAS == DMG_NERVEGAS) return Plugin_Continue; //Saw blade
	#endif
	
	//Ignore if headshot or backstab
	if (iDamageType == TF_DMG_RIFLE_CRIT) return Plugin_Continue;
	if (iDamageType == TF_DMG_MELEE_CRIT && (GetPlayerClass(iAttacker) == CLASS_SPY) && (fDamage >= 4.0 * float(GetClientMaxHealth(iVictim)))) return Plugin_Continue;

	//Check if player has metal return attribute
	if (ClientHasAttribute(iAttacker, iSlot, 299) && ClientHasAttribute(iAttacker, iSlot, 301) && (GetPlayerClass(iAttacker) == CLASS_ENGINEER)) {
		GiveEngineerMetal(iAttacker, RoundFloat(fDamage));
	}
	
	new Float:fDelay = GetClientAttribute(iVictim, _, ATTRIBUTE_DAMAGE_TAKEN_DELAYED_AFTER_LUNCH) + 0.1;
	new Handle:hData = CreateDataPack();
	WritePackCell(hData, iVictim);
	WritePackCell(hData, RoundFloat(fDamage));
	WritePackCell(hData, iAttacker);
	WritePackCell(hData, iDamageType | TF_DMG_DELAY);
	CreateTimer(fDelay, Attribute_1152_DealDamage, hData);
	
	//0.1 damage to allow for afterburn and other conditions to apply
	fDamage = 0.1;
	return Plugin_Changed;
}

public Action:Attribute_1152_DealDamage(Handle:hTimer, Handle:hData)
{
	ResetPack(hData);
	new iVictim = ReadPackCell(hData);
	new iDamage = ReadPackCell(hData);
	new iAttacker = ReadPackCell(hData);
	new iDamageType = ReadPackCell(hData);
	if (iDamageType & TF_DMG_DELAY == TF_DMG_DELAY) {
		if (IsValidClient(iVictim) && IsPlayerAlive(iVictim)) {
			if (IsValidClient(iAttacker)) {
				DealDamage(iVictim, iDamage, iAttacker, iDamageType);
			}
		}
	}
	CloseHandle(hData);	
}
