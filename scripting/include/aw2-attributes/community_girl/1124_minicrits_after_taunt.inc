#define ATTRIBUTE_MINICRITS_AFTER_TAUNTING            1124

new bool:g_bWasMiniCrit[MAXPLAYERS+1] = false;

public Attribute_1124_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Taunting) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_MINICRITS_AFTER_TAUNTING)) return;

    new iSlot = GetClientSlot(iClient);
    
    new Float:fDuration = GetClientAttribute(iClient, iSlot, ATTRIBUTE_MINICRITS_AFTER_TAUNTING);
    
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MINICRITS_AFTER_TAUNTING)) return;
    
    TF2_AddCondition(iClient, TFCond_Buffed, fDuration);
    g_bWasMiniCrit[iClient] = true;
    CreateTimer(fDuration, Attribute_MiniCritsTaunt, iClient);
}


//Directly hooked from advancedweaponiser2.sp
public Action:ClientSwitch_Attribute(iClient, iEntity)
{
    if (!IsValidEdict(iEntity)) return;
    if (!IsValidClient(iClient)) return;
    if (!g_bWasMiniCrit[iClient]) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_MINICRITS_AFTER_TAUNTING)) return;
    
    TF2_RemoveCondition(iClient, TFCond_Buffed);
    g_bWasMiniCrit[iClient] = false;
}

public Action:Attribute_MiniCritsTaunt(Handle:hTimer, any:iClient) 
{
    g_bWasMiniCrit[iClient] = false;
}

Attribute_1124_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!g_bWasMiniCrit[iClient]) return iButtons;
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MINICRITS_AFTER_TAUNTING)) {
    return iButtons;
    }
    if (ClientHasAttribute(iClient, _, ATTRIBUTE_MINICRITS_AFTER_TAUNTING)) {
    TF2_RemoveCondition(iClient, TFCond_Buffed);
    g_bWasMiniCrit[iClient] = false;
    }
    return iButtons;
}
    