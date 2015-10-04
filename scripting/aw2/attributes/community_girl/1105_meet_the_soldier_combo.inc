#define ATTRIBUTE_MEET_THE_SOLDIER_ALT_FIRE         1105

new bool:g_bSoldierBuffing1105[MAXPLAYERS+1] = false;
new bool:g_bHealing1105[MAXPLAYERS+1] = false;
new g_i1105Healer[MAXPLAYERS+1] = -1;
new g_i1105HealTarget[MAXPLAYERS+1] = -1;

Attribute_1105_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SOME_ALT_FIRE_DISABLED))
	{
		if (iButtons & IN_ATTACK2 == IN_ATTACK2)
		{
                new Float:fRage1105 = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
                if (!g_bSoldierBuffing1105[iClient] && fRage1105 >= 25.0) {
                g_bSoldierBuffing1105[iClient] = true;
                fRage1105 -= 25.0;
                SetEntPropFloat(iClient, Prop_Send, "m_flRageMeter", fRage1105);
                CreateTimer(8.0, Attribute_1105_Expire, iClient);
                AttachParticle(iClient, PARTICLE_RAGE_BUFF, 8.0);
                }
            }
        }
        new iTarget = GetHealTarget(iClient);
        if(TF2_GetPlayerClass(iClient) != TFClass_Medic) return iButtons;
        if (!IsValidClient(iTarget)) return iButtons;
        if (ClientHasAttribute(iTarget, iSlot, ATTRIBUTE_SOME_ALT_FIRE_DISABLED) && g_bSoldierBuffing1105[iTarget])
            {
            g_i1105Healer[iTarget] = iClient;
            g_bHealing1105[iClient] = true;
            g_i1105HealTarget[iClient] = iTarget;
            CreateTimer(1.0, Attribute_1105_ExpireDmgReduc, iClient);
            }
        return iButtons;
    }

public Action:Attribute_1105_Expire(Handle:hTimer, any:iClient) 
{
    g_bSoldierBuffing1105[iClient] = false;
    g_i1105Healer[iClient] = -1;
}

public Action:Attribute_1105_ExpireDmgReduc(Handle:hTimer, any:iClient) 
{
    if(TF2_GetPlayerClass(iClient) != TFClass_Medic) return;
    new iTarget = GetHealTarget(iClient);
    if (!IsValidClient(iTarget)) return;
    g_i1105Healer[iClient] = -1;
    g_bHealing1105[iClient] = false;
    g_i1105HealTarget[iClient] = -1;
}

public Action:Attribute_1105_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_MEET_THE_SOLDIER_ALT_FIRE)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
        
    if (g_bHealing1105[iVictim]) {
    fDamage *= 0.5;
    new iClient = g_i1105HealTarget[iVictim];
    new iDamage = RoundToFloor(fDamage);
    DealDamage(iClient, iDamage);
    }
    
    return Plugin_Changed;
}
