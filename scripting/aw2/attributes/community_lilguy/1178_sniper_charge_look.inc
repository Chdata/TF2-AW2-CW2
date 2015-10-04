#define ATTRIBUTE_SNIPER_CHARGE_LOOK	1178

new g_iSniperLookTime1178[MAXPLAYERS+1] = 0;
new Float:g_fSniperCharge1178[MAXPLAYERS+1] = 0.0;

public Attribute_1178_OnConditionAdded(iClient, TFCond:condition) {
	if (condition != TFCond_Zoomed) return;
	new iSlot = GetClientSlot(iClient);
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SNIPER_CHARGE_LOOK)) return;

	g_iSniperLookTime1178[iClient] = 0;
	g_fSniperCharge1178[iClient] = 0.0;
}

Attribute_1178_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SNIPER_CHARGE_LOOK)) return iButtons;
	if (!TF2_IsPlayerInCondition(iClient, TFCond_Zoomed)) return iButtons;

	new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
	new Float:fCurCharge = GetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage");

	//I was able to see through walls
	//Testing if 'false' would allow player to see world, not just targets	
	new iTarget = GetClientAimTarget(iClient, false);
	if (iTarget <= -1) return iButtons;
	if (!IsValidClient(iTarget)) return iButtons;

	new iTeam = GetClientTeam(iClient);
	if (GetClientTeam(iTarget) == iTeam) return iButtons;
	//For glow, should work with 1130_reveal_on_combohit glow condition detect
	if ((!IsCloaked(iTarget)) || (!IsDisguised(iTarget))) {
		TF2_AddCondition(iTarget, TFCond_Unknown2, 0.2);
	}

	if (fCurCharge >= 150.0) return iButtons;

	//Client attribute denotes time in seconds to increment charge by 1 percent
	//0.5 for every 0.5 seconds, 1.2 for every 1.2 seconds
	g_iSniperLookTime1178[iClient] += 1;
	new iChargeInt = RoundToCeil(GetClientAttribute(iClient, iSlot, ATTRIBUTE_SNIPER_CHARGE_LOOK) * 60.0);

	if (g_iSniperLookTime1178[iClient] >= iChargeInt) {
		//1.5 charge = 1% of in-game Sniper charge
		g_fSniperCharge1178[iClient] += 1.5;

		if (g_fSniperCharge1178[iClient] >= 150.0) g_fSniperCharge1178[iClient] = 150.0;

		SetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage", g_fSniperCharge1178[iClient]);
		g_iSniperLookTime1178[iClient] = 0;
	}
	return iButtons;
}

Attribute_1178_OnInventory(iClient, iSlot) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SNIPER_CHARGE_LOOK)) return;
	g_iSniperLookTime1178[iClient] = 0;
	g_fSniperCharge1178[iClient] = 0.0;
}
