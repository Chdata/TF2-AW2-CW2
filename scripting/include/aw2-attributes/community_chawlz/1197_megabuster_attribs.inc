#define ATTRIBUTE_MEGABUSTER	 1197


new g_iShots1197[MAXPLAYERS+1] = 0;

Attribute_1197_Precache()
{
	SuperPrecacheSound(SOUND_MEGABUSTER_SHOOT);
}

Attribute_1197_OnAttack(iClient, iSlot, &bool:bCrit)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEGABUSTER)) return;
	if (g_iShots1197[iClient] >= 3) return;

	EmitSoundToAll(SOUND_MEGABUSTER_SHOOT, iClient);

	g_iShots1197[iClient] += 1;
	CreateTimer(1.0, Attribute_1197_Timer, iClient);
	//PrintToChat(iClient, "fired %d", g_iShots1197[iClient]);

	return;
}

Attribute_1197_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEGABUSTER)) return iButtons;
	if ((iButtons & IN_ATTACK == IN_ATTACK)&& (g_iShots1197[iClient] >= 3))
		{
		iButtons &= ~IN_ATTACK;

		}
	return iButtons;
}

public Action:Attribute_1197_Timer(Handle:hTimer, any:iClient) 
{
	if (g_iShots1197[iClient] >> 0)
		g_iShots1197[iClient] -= 1;

	//PrintToChat(iClient, "recovered %d", g_iShots1197[iClient]);
}

Attribute_1197_ProjCreated(iEntity, &iClient, &iSlot)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEGABUSTER)) return;
	if (!IsValidEdict(iEntity)) return;

	//This should paint the projectile yellow I guess?
	
	//decl rgba[4];
	//rgba[0] = 255; rgba[1] = 255; rgba[2] = 0;rgba[3] = 255;
	SetEntityRenderColor(iEntity, 255, 255, 0, 255);

}

public Action:Attribute_1197_PStartTouch(iEntity, iOther, iOwner, iSlot)
{
	if (!ClientHasAttribute(iOwner, iSlot, ATTRIBUTE_MEGABUSTER)) return Plugin_Continue;
	if (IsValidClient(iOther)) return Plugin_Continue;
	if (IsEntityBuilding(iOther)) return Plugin_Continue;
	
	if (IsClassname(iEntity, "tf_projectile_rocket")) {
		RemoveEdict(iEntity);
	}
	
	//PrintToChat(iOwner, "Projectile bounce");
	return Plugin_Handled;
}