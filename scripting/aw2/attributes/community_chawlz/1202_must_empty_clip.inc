#define ATTRIBUTE_MUST_EMPTY_CLIP		   1202

#define SOUND_PISTOL_SHOOT				   "weapons/pistol_shoot.wav"

new g_iShotsFired1202[MAXPLAYERS+1] = 0;
new Float:g_fLastShotFired1202[MAXPLAYERS+1] = 0.0;
new bool:g_bMustKeepFiring1202[MAXPLAYERS+1] = false;

Attribute_1202_Precache()
{
	SuperPrecacheSound(SOUND_PISTOL_SHOOT);
}

Attribute_1202_OnInventory(iClient, iSlot)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MUST_EMPTY_CLIP)) return;

	g_bMustKeepFiring1202[iClient] = false;
	g_iShotsFired1202[iClient] = 0;
}

Attribute_1202_OnAttack(iClient, iSlot, &bool:bCrit)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MUST_EMPTY_CLIP)) return;
	if (!g_bMustKeepFiring1202[iClient])
		{
		g_bMustKeepFiring1202[iClient] = true;
		PrintToChat(iClient, "started firing");
		}
	g_fLastShotFired1202[iClient] = GetGameTime();
}

Attribute_1202_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MUST_EMPTY_CLIP))
		{
		if (ClientHasAttribute(iClient, _, ATTRIBUTE_MUST_EMPTY_CLIP) && g_bMustKeepFiring1202[iClient])
			{
			SetClientSlot(iClient, 1);
			}
		return iButtons;
		}
	new Float:fTime = GetGameTime();
	new Float:fFireRate = 0.17;
	
	if (ClientHasAttribute(iClient, iSlot, 5)) fFireRate *= GetClientAttribute(iClient, iSlot, 5);
	if (ClientHasAttribute(iClient, iSlot, 6)) fFireRate *= GetClientAttribute(iClient, iSlot, 6);
		
	if (g_bMustKeepFiring1202[iClient] && fTime >= g_fLastShotFired1202[iClient]+fFireRate)
		{
		PrintToChat(iClient, "tick");
		//PrintToChat(iClient, "Time: %.1f", fTime);
		
		//new iClipSize = 12;
		new iClip = GetEntProp(iSlot, Prop_Send, "m_iClip1");
		
		//if (ClientHasAttribute(iClient, iSlot, 3)) iClipSize = RoundToCeil(iClipSize*GetClientAttribute(iClient, iSlot, 3));
		//if (ClientHasAttribute(iClient, iSlot, 4)) iClipSize = RoundToCeil(iClipSize*GetClientAttribute(iClient, iSlot, 4));
		
		
		
		fTime += fFireRate;
		g_fLastShotFired1202[iClient] = fTime;
		
		if (iClip > 0)
			{
				//SetEntPropFloat(iClient, Prop_Send, "m_flNextAttack", fTime);
				iButtons = IN_ATTACK;
				//PrintToChat(iClient, "pew");
				PrintToChat(iClient, "Shots left: %i", iClip);
				EmitSoundToClient(iClient, SOUND_PISTOL_SHOOT);
				g_iShotsFired1202[iClient] += 1;
			}
		else
			{
			g_bMustKeepFiring1202[iClient] = false;
			g_iShotsFired1202[iClient] = 0;
			PrintToChat(iClient, "clip empty");
			}
		}

	return iButtons;
}
