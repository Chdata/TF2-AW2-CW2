#define ATTRIBUTE_NOCRITCHARGE         1120

new bool:g_bIsCharging1120[MAXPLAYERS+1] = false;

//Attribute_1120_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
//{
//    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_NOCRITCHARGE)) return iButtons;
//    if (!TF2_IsPlayerInCondition(iClient, TFCond_Charging)) return iButtons;
//    if (!IsValidClient(iClient)) return iButtons;
    
//    TF2_RemoveCondition(iClient, TFCond_Kritzkrieged);
    
//    return iButtons;
//}

public Attribute_1120_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_NOCRITCHARGE)) return;
    if (condition != TFCond_Charging) return;

    g_bIsCharging1120[iClient] = true;
    
    return;
}

public Attribute_1120_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_NOCRITCHARGE)) return;
    if (condition != TFCond_Charging) return;
   
    CreateTimer(2.0, Attribute_1120_Expire, iClient);
    
    return;
}


public Action:Attribute_1120_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!ClientHasAttribute(iAttacker, _, ATTRIBUTE_NOCRITCHARGE)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!g_bIsCharging1120[iAttacker]) return Plugin_Continue;

    if ((iDamageType & TF_DMG_MELEE_CRIT == TF_DMG_MELEE_CRIT))
        {
        iDamageType = TF_DMG_MELEE;
        ApplyMinicrit(iVictim, iAttacker);
        return Plugin_Changed;
        }

    
    return Plugin_Continue;
}

public Action:Attribute_1120_Expire(Handle:hTimer, any:iClient) 
{
    g_bIsCharging1120[iClient] = false;
}