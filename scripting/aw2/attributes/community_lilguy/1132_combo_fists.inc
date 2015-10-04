#define ATTRIBUTE_COMBO_FISTS	1132

new g_iFistCombo1132[MAXPLAYERS+1] = 0;
new g_iHitPending1132[MAXPLAYERS+1] = 0;
new bool:g_bFistComboHit1132[MAXPLAYERS+1] = false;

//girl added a sound effect~

Attribute_1132_OnInventory(iClient, iSlot)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_COMBO_FISTS)) return;
	g_iFistCombo1132[iClient] = 0;
}

Attribute_1132_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	//1 for attack 1 (left), 2 for attack 2 (right)
	//Appends last hit to the end of int
	//So 112 means left, left, right
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_COMBO_FISTS)) {
		if (iButtons & IN_ATTACK == IN_ATTACK) {
			g_bFistComboHit1132[iClient] = false;
			g_iHitPending1132[iClient] = 1;
		} else if (iButtons & IN_ATTACK2 == IN_ATTACK2) {
			g_bFistComboHit1132[iClient] = false;
			g_iHitPending1132[iClient] = 2;
		}
	}
	return iButtons;
}

public Action:Attribute_1132_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding) {
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (!IsValidClient(iVictim)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_COMBO_FISTS)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (IsAfterDamage(iDamageType)) return Plugin_Continue;
	if (bBuilding) return Plugin_Continue;
	
	g_bFistComboHit1132[iAttacker] = true;

	if (g_iHitPending1132[iAttacker] != 0) 
	{
		if (g_iHitPending1132[iAttacker] == 1) {
			PrintToChat(iAttacker, "LEFT!");
			g_iFistCombo1132[iAttacker] *= 10;
			g_iFistCombo1132[iAttacker] += 1;
			g_iHitPending1132[iAttacker] = 0;
		} else if (g_iHitPending1132[iAttacker] == 2) {
			PrintToChat(iAttacker, "RIGHT!");
			g_iFistCombo1132[iAttacker] *= 10;
			g_iFistCombo1132[iAttacker] += 2;
			g_iHitPending1132[iAttacker] = 0;
		}
	}

	//Left start combos	
	if (g_iFistCombo1132[iAttacker] == 111) {
		//Short speed buff
		TF2_AddCondition(iAttacker, TFCond_SpeedBuffAlly, 4.0);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		PrintToChat(iAttacker, "RED CYCLONE!");
		g_iFistCombo1132[iAttacker] = 0;
	}
	else if (g_iFistCombo1132[iAttacker] == 112) {
		//Uppercut (Crit)
		iDamageType = MakeCritDamageType(iDamageType);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		g_iFistCombo1132[iAttacker] = 0;
		PrintToChat(iAttacker, "POW!");
		return Plugin_Changed;
	}
	else if (g_iFistCombo1132[iAttacker] == 121) {
		//HP gain
		new iAddHealth = RoundFloat(GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_COMBO_FISTS));
		new iHealthClient = GetClientHealth(iAttacker);
		new iMaxClient = GetClientMaxOverHeal(iAttacker);

		iHealthClient += iAddHealth;
		if (iHealthClient > iMaxClient) iHealthClient = iMaxClient;

		SetEntityHealth(iAttacker, iHealthClient);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		PrintToChat(iAttacker, "FEEDING TIME!");
		g_iFistCombo1132[iAttacker] = 0;
	}
	else if (g_iFistCombo1132[iAttacker] == 122) {
		//Bleed
		TF2_MakeBleed(iVictim, iAttacker, 8.0);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		PrintToChat(iAttacker, "'SO MUCH BLOOD!'");
		g_iFistCombo1132[iAttacker] = 0;
	}
	//Right start combos
	else if (g_iFistCombo1132[iAttacker] == 222) {
		//300% scale pushback (From Eternal Sleeper/Prod Stick)
		new Float:fScale = 4.0;

		decl Float:vAng[3], Float:vVelocity[3];
		GetClientEyeAngles(iAttacker, vAng);
		vAng[0] = -40.0;
		AnglesToVelocity(vAng, vVelocity, 200.0 * fScale);

		TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vVelocity);

		g_iFistCombo1132[iAttacker] = 0;
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		PrintToChat(iAttacker, "COSMONAUT LAUNCHER!");
		return Plugin_Changed;
	}
	else if (g_iFistCombo1132[iAttacker] == 221) {
		//1 sec uber
		TF2_AddCondition(iAttacker, TFCond_Ubercharged, 1.0);
		PrintToChat(iAttacker, "IRON CURTAIN!!");
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		g_iFistCombo1132[iAttacker] = 0;
	}
	else if (g_iFistCombo1132[iAttacker] == 212) {
		//HP gain
		new iAddHealth = RoundFloat(GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_COMBO_FISTS));
		new iHealthClient = GetClientHealth(iAttacker);
		new iMaxClient = GetClientMaxOverHeal(iAttacker);

		iHealthClient += iAddHealth;
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		if (iHealthClient > iMaxClient) iHealthClient = iMaxClient;

		SetEntityHealth(iAttacker, iHealthClient);
		PrintToChat(iAttacker, "FEEDING TIME!");
		g_iFistCombo1132[iAttacker] = 0;
	}
	else if (g_iFistCombo1132[iAttacker] == 211) {
		//Short minicrit buff
		TF2_AddCondition(iAttacker, TFCond_Buffed, 3.0);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		EmitSoundToAll(SOUND_COMBO_HEAVY, iAttacker);
		PrintToChat(iAttacker, "SOVIET FURY!");
		g_iFistCombo1132[iAttacker] = 0;
	}

	return Plugin_Continue;
}
