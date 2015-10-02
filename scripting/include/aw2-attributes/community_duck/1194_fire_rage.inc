#define ATTRIBUTE_FIRE_RAGE		  1194

#define ATTRIBUTE_1194_DISTANCE_LIMIT			   450.0

new bool:g_f1194RageIsActive[MAXPLAYERS+1];
new bool:g_f1194BuffedByFire[MAXPLAYERS+1];
new g_i1194DrainTimer[MAXPLAYERS+1];

public Attribute_1194_Init()
{
	AddRecharge(ATTRIBUTE_FIRE_RAGE, "Rage");
}

Attribute_1194_OnInventory(iClient, iSlot)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FIRE_RAGE)) return;
	SetClientRecharge(iClient, ATTRIBUTE_FIRE_RAGE, 0.0);
}

Attribute_1194_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!ClientHasAttribute(iClient, _, ATTRIBUTE_FIRE_RAGE)){g_f1194BuffedByFire[iClient] = false; return iButtons;}
	
	g_i1194DrainTimer[iClient] += 1; //every 12 frames this variable resets to 0
	
	if (g_i1194DrainTimer[iClient] >= 12)
	{
		if (g_f1194RageIsActive[iClient])
		{
			g_i1194DrainTimer[iClient] = 0;
			new Float:fRage = GetClientRecharge(iClient, ATTRIBUTE_FIRE_RAGE);
			if (fRage > 0.0)
			{
				AddClientRecharge(iClient, ATTRIBUTE_FIRE_RAGE, -1.0);//Drain rage
				
				new Float:ClientPos[3];
				GetClientAbsOrigin(iClient, ClientPos);
				new Float:TeammatePos[3];
				new Float:TeammateDist;
				
				for (new iTeammate = 1; iTeammate <= MaxClients ; iTeammate++)//BUFF NEARBY TEAMMATES
				{
					if(iTeammate == iClient) return iButtons;
					if(!IsValidClient(iTeammate)) return iButtons;
					if(GetClientTeam(iTeammate) != GetClientTeam(iClient)) return iButtons;
					
					GetClientAbsOrigin(iTeammate, TeammatePos);
					TeammateDist = GetVectorDistance(ClientPos, TeammatePos);
					
					if(TeammateDist < 450.0)
					{
						g_f1194BuffedByFire[iTeammate] = true;
					}
					else
					{
						g_f1194BuffedByFire[iTeammate] = false;
					}
				}
				return iButtons;
			}
			if (fRage == 0.0)
			{
				g_f1194RageIsActive[iClient] = false;
			}
		}
	}
	
	return iButtons;
}

//Turn rage mode on if you taunt with full rage
public Attribute_1194_OnConditionAdded(iClient, TFCond:condition)
{
	if (!IsValidClient(iClient)) return;
	if (condition != TFCond_Taunting) return;
	if (!OnGround(iClient)) return;
	new iSlot = GetClientSlot(iClient);
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FIRE_RAGE)) return;
	if (!IsRechargeMax(iClient, ATTRIBUTE_FIRE_RAGE)) return;
	
	g_f1194RageIsActive[iClient] = true;
}

public Action:Attribute_1194_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (bBuilding) return Plugin_Continue;
	if (g_f1194BuffedByFire[iAttacker])
	{
		if (!ClientHasAttribute(iAttacker, _, ATTRIBUTE_FIRE_RAGE))
		{
			TF2_IgnitePlayer(iVictim, iAttacker);//Ignition for rage reciever
			fDamage *= 1.15;//Damage bonus for rage reciever
			return Plugin_Changed;
		}
	}
	if (!ClientHasAttribute(iAttacker, _, ATTRIBUTE_FIRE_RAGE)) return Plugin_Continue;
	new Float:fRageAdd = fDamage * GetClientAttribute(iAttacker, _, ATTRIBUTE_FIRE_RAGE);
	if (g_f1194RageIsActive[iAttacker])
	{
		fDamage *= 1.15;//Damage bonus for rage user
		fRageAdd = 2 * fDamage * GetClientAttribute(iAttacker, _, ATTRIBUTE_FIRE_RAGE);//Rage generation bonus
		TF2_IgnitePlayer(iVictim, iAttacker);//Ignition for rage user
		AddClientRecharge(iAttacker, ATTRIBUTE_FIRE_RAGE, fRageAdd);
		return Plugin_Changed;
	}
	AddClientRecharge(iAttacker, ATTRIBUTE_FIRE_RAGE, fRageAdd);//Rage generation on hit
	return Plugin_Continue;
}
