#define ATTRIBUTE_DEF_RAGE_BONUS	1181

new Float:g_f1181Rage[MAXPLAYERS+1] = 0.0;

Attribute_1181_OnInventory(iClient, iSlot)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DEF_RAGE_BONUS)) return;
	new Float:fRage = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");

	//DEBUG
	PrintToChat(iClient, "%f rage", fRage);

	g_f1181Rage[iClient] = fRage;
}

Attribute_1181_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DEF_RAGE_BONUS)) return iButtons;
	//Attribute 116 is Soldier buff type
	if (!ClientHasAttribute(iClient, 1, 116)) return iButtons;
	new iBuffType = RoundFloat(GetClientAttribute(iClient, 1, 116));
	if (iBuffType != 2 && iBuffType != 3) return iButtons;

	new Float:fRage = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
	if (fRage <= g_f1181Rage[iClient]) return iButtons;
	//Get the difference
	new Float:fDiff = fRage - g_f1181Rage[iClient];
	new Float:fBonus = GetClientAttribute(iClient, iSlot, ATTRIBUTE_DEF_RAGE_BONUS) * fDiff;
	
	//DEBUG
	PrintToChat(iClient, "Rage gain: %f", fDiff);
	PrintToChat(iClient, "Def rage bonus: %f", fBonus);

	fRage += fBonus;
	if (fRage > 100.0) fRage = 100.0;
	SetEntPropFloat(iClient, Prop_Send, "m_flRageMeter", fRage);

	g_f1181Rage[iClient] = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
	return iButtons;
}

