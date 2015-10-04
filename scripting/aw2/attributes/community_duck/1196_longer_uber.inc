#define ATTRIBUTE_UBER_DURATION		 1196
//longer ubercharge
new g_iRegenUberTime1196[MAXPLAYERS+1] = 0;

Attribute_1196_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!ClientHasAttribute(iClient, _, ATTRIBUTE_UBER_DURATION)) return iButtons;
	
	g_iRegenUberTime1196[iClient] += 1;
	
	if (g_iRegenUberTime1196[iClient] >= 120)
	{
		g_iRegenUberTime1196[iClient] = float:GetClientAttribute(iClient, _, ATTRIBUTE_UBER_DURATION);
		new Float:fUber = TF2_GetPlayerUberLevel(iClient);
		if (IsUberchargeDeployed(iClient))
		{
			fUber += 1.0;
			TF2_SetPlayerUberLevel(iClient, fUber);
		}
	}
	
	return iButtons;
}