#define ATTRIBUTE_UBER_REGEN		 1186
//Regenerate x% uber per second
new g_iRegenUberTime[MAXPLAYERS+1] = 0;

Attribute_1186_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!ClientHasAttribute(iClient, _, ATTRIBUTE_UBER_REGEN)) return iButtons;
	
	g_iRegenUberTime[iClient] += 1;
	
	if (g_iRegenUberTime[iClient] >= 120)
	{
		g_iRegenUberTime[iClient] = 0;
		new Float:fUber = TF2_GetPlayerUberLevel(iClient);
		if (fUber < 100.0)
		{
			fUber += 100.0*GetClientAttribute(iClient, _, ATTRIBUTE_UBER_REGEN);
			TF2_SetPlayerUberLevel(iClient, fUber);
		}
	}
	
	return iButtons;
}