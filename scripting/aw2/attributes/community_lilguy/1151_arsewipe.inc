#define ATTRIBUTE_ARSEWIPE 1151

//0 = Jarate, 1 = Milk, 2 = Bleed
//All default to false when initialized
new bool:g_bArseCondition[MAXPLAYERS+1][3];

Attribute_1151_OnInventory(iClient, iSlot) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ARSEWIPE)) return;

	new iLoop;
	for (iLoop = 0; iLoop < 3; iLoop++) {
		g_bArseCondition[iClient][iLoop] = false;
	}
}

Attribute_1151_OnAttack(iClient, iSlot, &bool:bCrit) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ARSEWIPE)) return;
	new iTarget = GetClientAimTarget(iClient, true);
	//-1 for not found, -2 for plugin not supported
	if (iTarget <= -1) return;
	if (!IsValidClient(iTarget)) return;

	new iTeam = GetClientTeam(iClient);
	if (GetClientTeam(iTarget) != iTeam) return;

	decl Float:vClientPos[3];
	GetClientAbsOrigin(iClient, vClientPos);
	decl Float:vTargetPos[3];
	GetClientAbsOrigin(iTarget, vTargetPos);
	
	new Float:fDistance;
	fDistance = GetVectorDistance(vTargetPos, vClientPos);

	//Normal melee range is aprox 65HU
	if (fDistance <= 80.0) {
		if (TF2_IsPlayerInCondition(iTarget, TFCond_Jarated)) {
			TF2_RemoveCondition(iTarget, TFCond_Jarated);
			if (!g_bArseCondition[iClient][0]) {
				g_bArseCondition[iClient][0] = true;
			}
		}
		if (TF2_IsPlayerInCondition(iTarget, TFCond_Milked)) {
			TF2_RemoveCondition(iTarget, TFCond_Milked);
			if (!g_bArseCondition[iClient][1]) {
				g_bArseCondition[iClient][1] = true;
			}
		}
		if (TF2_IsPlayerInCondition(iTarget, TFCond_Bleeding)) {
			TF2_RemoveCondition(iTarget, TFCond_Bleeding);
			if (!g_bArseCondition[iClient][2]) {
				g_bArseCondition[iClient][2] = true;
			}
		}
	}	
	return;
}

public Action:Attribute_1151_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding) {
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (!IsValidClient(iVictim)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;

	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_ARSEWIPE)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (IsAfterDamage(iDamageType)) return Plugin_Continue;
	if (bBuilding) return Plugin_Continue;

	new iLoop;
	for (iLoop = 0; iLoop < 3; iLoop++) {
		if (g_bArseCondition[iAttacker][iLoop]) {
			if (iLoop == 0) {
				TF2_AddCondition(iVictim, TFCond_Jarated, 10.0);
			} else if (iLoop == 1) {
				TF2_AddCondition(iVictim, TFCond_Milked, 10.0);
			} else {
				TF2_MakeBleed(iVictim, iAttacker, 8.0);
			}
			g_bArseCondition[iAttacker][iLoop] = false;
		}

	}
	return Plugin_Continue;
}
