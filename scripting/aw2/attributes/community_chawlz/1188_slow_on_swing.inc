#define ATTRIBUTE_SLOW_ON_SWING	  1188

new bool:g_bPlayerIsSwinging1188[MAXPLAYERS+1] = false;


Attribute_1188_OnAttack(iClient, iSlot, &bool:bCrit)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SLOW_ON_SWING)) return;

	CreateTimer(0.7, Attribute_1188_Expire, iClient);
	g_bPlayerIsSwinging1188[iClient] = true;

	return;
}

public Action:Attribute_1188_Expire(Handle:hTimer, any:iClient) 
{
	g_bPlayerIsSwinging1188[iClient] = false;
	SetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed", TF2_GetClassSpeed(GetPlayerClass(iClient)));
}

Attribute_1188_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {

	if (!ClientHasAttribute(iClient, _, ATTRIBUTE_SLOW_ON_SWING)) return iButtons;

	if ((iButtons & IN_ATTACK == IN_ATTACK) && (!OnGround(iClient)) && (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SLOW_ON_SWING)))
		{
			iButtons &= ~IN_ATTACK;
		}

	if (g_bPlayerIsSwinging1188[iClient] == false) return iButtons;

	//new Float:fMaxSpeed = GetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed");
	//new Float:fClassSpeed = TF2_GetClassSpeed(GetPlayerClass(iClient));
	//if (fMaxSpeed <= 10.0) return iButtons;
	
	//new Float:fSpeed = GetClientAttribute(iClient, iSlot, ATTRIBUTE_SLOW_ON_SWING) * fClassSpeed;
	//if (fMaxSpeed != fSpeed) {
	SetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed", 15.0);
	//}
	
	return iButtons;
}

public Action:Attribute_1188_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;	
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_SLOW_ON_SWING)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	
	if (!OnGround(iAttacker))
		{
		fDamage = 0.0;
		return Plugin_Changed;
		}
	
	return Plugin_Continue;
}