#define ATTRIBUTE_ALL_RAGE_BONUS	1182

new Float:g_f1182Rage[MAXPLAYERS+1] = 0.0;

Attribute_1182_OnInventory(iClient, iSlot)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ALL_RAGE_BONUS)) return;
	new Float:fRage = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
	g_f1182Rage[iClient] = fRage;
}

Attribute_1182_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ALL_RAGE_BONUS)) return iButtons;

	new Float:fRage = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
	if (fRage <= g_f1182Rage[iClient]) return iButtons;
	//Get the difference
	new Float:fDiff = fRage - g_f1182Rage[iClient];
	new Float:fBonus = GetClientAttribute(iClient, iSlot, ATTRIBUTE_ALL_RAGE_BONUS) * fDiff;
	fRage += fBonus;
	if (fRage > 100.0) fRage = 100.0;
	SetEntPropFloat(iClient, Prop_Send, "m_flRageMeter", fRage);

	g_f1182Rage[iClient] = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
	return iButtons;
}

