#define ATTRIBUTE_DUCK_IS_BLOCK      1168

new bool:g_bIsBlocking1168[MAXPLAYERS+1] = false;
new bool:g_bBlockedRecently[MAXPLAYERS+1] = false;
new g_iBlockCountMax[MAXPLAYERS+1] = 0;

Attribute_1168_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (g_bIsBlocking1168[iClient]) return iButtons;
    if (g_bBlockedRecently[iClient]) return iButtons;
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DUCK_IS_BLOCK))
	{
		if (iButtons & IN_DUCK == IN_DUCK)
		{
        if (iButtons & IN_BACK == IN_BACK)
        {
        g_bIsBlocking1168[iClient] = true;
        new Float:fDuration1168 = GetClientAttribute(iClient, iSlot, ATTRIBUTE_DUCK_IS_BLOCK);
        CreateTimer(fDuration1168, Attribute_Block1168, iClient);
        fDuration1168 *= 1.5;
        CreateTimer(fDuration1168, Attribute_BlockOverload1168, iClient);
        }
        }
	}
    return iButtons;
}

public Action:Attribute_Block1168(Handle:hTimer, any:iClient) 
{
    if (!IsValidClient(iClient)) return;
    
    g_bIsBlocking1168[iClient] = false;
    g_iBlockCountMax[iClient] = 0;
    g_bBlockedRecently[iClient] = true;
}

public Action:Attribute_BlockOverload1168(Handle:hTimer, any:iClient) 
{
    if (!IsValidClient(iClient)) return;
    
    g_bBlockedRecently[iClient] = false;
}

public Action:Attribute_1168_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iVictim, _, ATTRIBUTE_DUCK_IS_BLOCK)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!g_bIsBlocking1168[iVictim]) return Plugin_Continue;
    if (g_iBlockCountMax[iVictim] <= 3) return Plugin_Continue;
    
    fDamage *= 0.5;
    g_iBlockCountMax[iVictim]++;
    EmitSoundToAll(SOUND_BLOCK_CROUCH, iVictim, _, SNDLEVEL_NORMAL);
    
    return Plugin_Changed;
}