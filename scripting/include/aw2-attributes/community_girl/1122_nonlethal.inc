#define ATTRIBUTE_NONLETHAL            1122

new Float:g_f1122Neardeath[MAXPLAYERS+1] = 0.0;

public Action:Attribute_1122_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_NONLETHAL)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (DamageWillKill(iVictim, fDamage, false))
	{    
    fDamage = 0.0;
    EmitSoundToAll(SOUND_1122_NOKILL, iVictim);
    SetEntityHealth(iVictim, 1);
    g_f1122Neardeath[iVictim] = GetEngineTime();
    }
    
    return Plugin_Changed;
}

Attribute_1122_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (g_f1122Neardeath[iClient] >= GetEngineTime())
    {
        SetEntityHealth(iClient, 1);
    }
    
    return iButtons;
}