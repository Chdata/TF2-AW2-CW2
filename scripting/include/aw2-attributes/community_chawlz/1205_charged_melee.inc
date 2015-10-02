#define ATTRIBUTE_CHARGED_MELEE		   1205

#define SOUND_PISTOL_SHOOT				   "weapons/pistol_shoot.wav"

new Float:g_fChargeStart1205[MAXPLAYERS+1] = 0.0;
new Float:g_fChargeLevel1205[MAXPLAYERS+1] = 1.0;
new bool:g_bIsCharging1205[MAXPLAYERS+1] = false;

Attribute_1205_OnAttack(iClient, iSlot, &bool:bCrit)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CHARGED_MELEE)) return;
	new Float:fTime = GetGameTime();
	new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
	
	g_bMustKeepFiring1202[iClient] = true;
	PrintToChat(iClient, "started firing");
	EmitSoundToAll(SOUND_CHARGE_STICKYBOMB, iClient);
	SetEntPropFloat(iWeapon, Prop_Send, "m_fNextAttack", fTime+3.0);
	
	g_fChargeStart1205[iClient] = fTime;
	g_bIsCharging1205[iClient] = true;
}

Attribute_1205_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CHARGED_MELEE))
		{
		if (ClientHasAttribute(iClient, _, ATTRIBUTE_CHARGED_MELEE) && g_bIsCharging1205[iClient])
			{
			StopSound(iClient, SNDCHAN_AUTO, SOUND_CHARGE_STICKYBOMB);
			g_fChargeLevel1205[iClient] = 1.0;
			}
		return iButtons;
		}
	
	new Float:fTime = GetGameTime();
	new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
			
	if (iButtons & IN_ATTACK == IN_ATTACK)
		{
		if (!g_bIsCharging1205[iClient])
			{
			//iButtons = ~IN_ATTACK
			return iButtons;
			}
		if (fTime < g_fChargeStart1205[iClient] + 3.0)
			{
			g_fChargeLevel1205[iClient]+= 0.02;
			if (g_fChargeLevel1205[iClient] > 5.0) g_fChargeLevel1205[iClient]= 5.0;
			}
		else
			{
			if (g_bIsCharging1205[iClient])
				{
				//SetEntPropFloat(iWeapon, Prop_Send, "m_fNextAttack", fTime);
				CreateTimer(0.4, Attribute_1205_Expire, iClient);
				}
			}
		}
	else
		{
		iButtons = IN_ATTACK;
		SetEntPropFloat(iWeapon, Prop_Send, "m_fNextAttack", fTime);
		StopSound(iClient, SNDCHAN_AUTO, SOUND_CHARGE_STICKYBOMB);
		}
	return iButtons;
}

public Action:Attribute_1205_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_CHARGED_MELEE)) return Plugin_Continue;

	fDamage *= g_fChargeLevel1205[iAttacker];
	g_fChargeLevel1205[iAttacker] = 1.0;
	
	return Plugin_Changed;
}

public Action:Attribute_1205_Expire(Handle:hTimer, any:iClient) 
{
    g_fChargeLevel1205[iClient] = 1.0;
}