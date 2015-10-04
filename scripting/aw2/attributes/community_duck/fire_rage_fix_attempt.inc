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
	if (!ClientHasAttribute(iClient, _, ATTRIBUTE_FIRE_RAGE)) return iButtons;
	
	g_i1194DrainTimer[iClient] += 1;
	
	if (g_i1194DrainTimer[iClient] >= 5)
	{
		if (g_f1194RageIsActive[iClient])
		{
			g_i1194DrainTimer[iClient] = 0;
			new float:fRage = GetClientRecharge(iClient, ATTRIBUTE_EVASIVENESS_ON_HIT);
			if (fRage > 0.0)
			{
				AddClientRecharge(iClient, ATTRIBUTE_UBER_ON_NEARDEATH, -1.0);//Drain rage
				////////////////////////////////////////////////////////////////////////////////////////////////////INSERT BUFF NEARBY TEAMMATES HERE//
				return iButtons;
			}
			if (fRage > 0.0)
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
	if (!IsValidClient(iClient)) return Plugin_Continue;
	if (condition != TFCond_Taunting) return Plugin_Continue;
	if (!OnGround(iClient)) return Plugin_Continue;
	new iSlot = GetClientSlot(iClient);
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FIRE_RAGE)) return Plugin_Continue;
	if (!IsRechargeMax(iClient, ATTRIBUTE_FIRE_RAGE)) return Plugin_Continue;
	
	g_f1194RageIsActive[iClient] = true;
	return Plugin_Continue;
}

public Action:Attribute_1194_OnTakeDamage(iVictim, &iAttacker, iSlot, &float:fDamage, &iDamageType, float:fForce[3], float:fForcePos[3], bool:bBuilding)
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
	fDamage *= 1.15;//Damage bonus for rage user
	TF2_IgnitePlayer(iVictim, iAttacker);//Ignition for rage user
	new float:fRageAdd = fDamage * GetClientAttribute(iAttacker, _, ATTRIBUTE_FIRE_RAGE);
	AddClientRecharge(iAttacker, ATTRIBUTE_UBER_ON_NEARDEATH, fRageAdd);//Rage generation on hit
	if (!g_f1194RageIsActive[iAttacker]) return Plugin_Continue;
	AddClientRecharge(iAttacker, ATTRIBUTE_UBER_ON_NEARDEATH, fRageAdd);//Double rage generation during rage. This allows the user to make long pushes if they deal tons of damage
	return Plugin_Changed;
}
