#define ATTRIBUTE_INJECTION_ON_HIT          1046

new bool:g_b1046Healing[MAXPLAYERS+1] = false;

public Attribute_1046_Init()
{
    AddRecharge(ATTRIBUTE_INJECTION_ON_HIT, "Injection", 0.0, 400.0, false, false);
}

public Action:Attribute_1046_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_INJECTION_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fInjection = fDamage * GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_INJECTION_ON_HIT);
    AddClientRecharge(iAttacker, ATTRIBUTE_INJECTION_ON_HIT, fInjection);

    new Float:fValue = GetClientRecharge(iAttacker, ATTRIBUTE_INJECTION_ON_HIT);
    if (fValue >= 400.0) {
        SlagInv_AddAchievementProgress(iAttacker, "aw2_painkiller");
    }
    
    return Plugin_Continue;
}

Attribute_1046_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_INJECTION_ON_HIT))
    {
        g_b1046Healing[iClient] = false;
        return iButtons;
    }
    new Float:fValue = GetClientRecharge(iClient, ATTRIBUTE_INJECTION_ON_HIT);
    if (fValue <= 0.0)
    {
        g_b1046Healing[iClient] = false;
        return iButtons;
    }
    
    new iTarget = GetHealTarget(iClient);
    if (!IsValidClient(iTarget))
    {
        g_b1046Healing[iClient] = false;
        return iButtons;
    }
    
    new iHealthClient = GetClientHealth(iClient);
    new iMaxClient = GetClientMaxOverHeal(iClient);
    new iHealthTarget = GetClientHealth(iTarget);
    new iMaxTarget = GetClientMaxOverHeal(iTarget);
    
    if (iHealthClient >= iMaxClient && iHealthTarget >= iMaxTarget)
    {
        g_b1046Healing[iClient] = false;
        return iButtons;
    }
    
    new Float:fValue2 = fValue - 1.0;
    if (fValue2 < 0.0) fValue2 = 0.0;
    SetClientRecharge(iClient, ATTRIBUTE_INJECTION_ON_HIT, fValue2);
    
    new Float:fDifference = fValue - fValue2;
    if (fDifference <= 0.0)
    {
        g_b1046Healing[iClient] = false;
        return iButtons;
    }
    
    iHealthClient += RoundFloat(fDifference);
    if (iHealthClient > iMaxClient) iHealthClient = iMaxClient;
    iHealthTarget += RoundFloat(fDifference);
    if (iHealthTarget > iMaxTarget) iHealthTarget = iMaxTarget;
    
    SetEntityHealth(iClient, iHealthClient);
    SetEntityHealth(iTarget, iHealthTarget);
    
    if (!g_b1046Healing[iClient])
    {
        EmitSoundToClient(iClient, SOUND_HL1_BELL, _, _, _, _, 0.5);
    }
    g_b1046Healing[iClient] = true;
    
    return iButtons;
}
