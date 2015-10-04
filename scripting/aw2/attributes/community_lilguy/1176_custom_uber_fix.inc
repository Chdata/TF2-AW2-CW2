#define ATTRIBUTE_MEDIGUN_CHARGE_FIX	1176

new Float:g_fUberAmount1176[MAXPLAYERS+1] = 0.0;
new g_iVal1176[MAXPLAYERS+1] = 0;

//Replenishes a players Ubercharge level when resupplies or respawns
//For convenience, use the item id # as the attribute value
Attribute_1176_OnInventory(iClient, iSlot)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEDIGUN_CHARGE_FIX)) return;

	CreateTimer(0.1, Attribute_1176_RestoreUber, iClient);
}

Attribute_1176_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!IsValidClient(iClient)) return iButtons;
	if (!IsPlayerAlive(iClient)) return iButtons;
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEDIGUN_CHARGE_FIX)) return iButtons;

	new iVal = RoundFloat(GetClientAttribute(iClient, iSlot, ATTRIBUTE_MEDIGUN_CHARGE_FIX));
	g_iVal1176[iClient] = iVal;

	new Float:fUber = TF2_GetPlayerUberLevel(iClient);
	g_fUberAmount1176[iClient] = fUber;
	return iButtons;
}	

public Action:Attribute_1176_RestoreUber(Handle:hTimer, any:iClient)
{
	if (!IsValidClient(iClient)) return;
	if (!IsPlayerAlive(iClient)) return;

	if (!ClientHasAttribute(iClient, 1, ATTRIBUTE_MEDIGUN_CHARGE_FIX)) return;
	new iVal = RoundFloat(GetClientAttribute(iClient, 1, ATTRIBUTE_MEDIGUN_CHARGE_FIX));
	if (iVal != g_iVal1176[iClient]) return;

	TF2_SetPlayerUberLevel(iClient, g_fUberAmount1176[iClient]);
}

Attribute_1176_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
	iSlot = 1;
	if (!IsValidClient(iClient)) return;
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEDIGUN_CHARGE_FIX)) return;
	g_fUberAmount1176[iClient] = 0.0;
}

