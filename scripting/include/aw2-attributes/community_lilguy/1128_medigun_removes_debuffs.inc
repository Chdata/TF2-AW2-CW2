#define ATTRIBUTE_MEDIGUN_REMOVES_DEBUFFS	1128

Attribute_1128_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEDIGUN_REMOVES_DEBUFFS)) {
		return iButtons;
	}
	new iTarget = GetHealTarget(iClient);
	if (!IsValidClient(iTarget)) {
		return iButtons;
	}

	//Remove debuffs except stun
	if(TF2_IsPlayerInCondition(iTarget, TFCond_OnFire)) {
		TF2_RemoveCondition(iTarget, TFCond_OnFire);
	}
	if(TF2_IsPlayerInCondition(iTarget, TFCond_Jarated)) {
		TF2_RemoveCondition(iTarget, TFCond_Jarated);
	}
	if(TF2_IsPlayerInCondition(iTarget, TFCond_Milked)){
	        TF2_RemoveCondition(iTarget, TFCond_Milked);
	}
	if(TF2_IsPlayerInCondition(iTarget, TFCond_Bleeding)) {
		TF2_RemoveCondition(iTarget, TFCond_Bleeding);
	}
	if(TF2_IsPlayerInCondition(iTarget, TFCond_MarkedForDeath)) {
		TF2_RemoveCondition(iTarget, TFCond_MarkedForDeath);
	}

	return iButtons;
}
