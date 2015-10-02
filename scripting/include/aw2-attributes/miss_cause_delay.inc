#define ATTRIBUTE_MISS_CAUSE_DELAY      1059

new Handle:g_hAttribute1059[MAXPLAYERS+1] = INVALID_HANDLE;
new bool:g_b1059LastWasMiss[MAXPLAYERS+1] = false;

Attribute_1059_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MISS_CAUSE_DELAY)) return;
    
    if (g_hAttribute1059[iClient] != INVALID_HANDLE) CloseHandle(g_hAttribute1059[iClient]);
    
    new Handle:hData = CreateDataPack();
    WritePackCell(hData, iClient);
    WritePackCell(hData, iSlot);
    g_hAttribute1059[iClient] = CreateTimer(0.0, Attribute_1059_Disable, hData, TIMER_DATA_HNDL_CLOSE);
    
    //PrintToChat(iClient, "OnAttack");
    
    if (g_b1059LastWasMiss[iClient]) EmitSoundToClient(iClient, SOUND_WEAPON_SHOTGUN);
    
    g_b1059LastWasMiss[iClient] = false;
}

public Action:Attribute_1059_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_MISS_CAUSE_DELAY)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (g_hAttribute1059[iAttacker] != INVALID_HANDLE) CloseHandle(g_hAttribute1059[iAttacker]);
    g_hAttribute1059[iAttacker] = INVALID_HANDLE;
    
    return Plugin_Continue;
}

public Action:Attribute_1059_Disable(Handle:hTimer, Handle:hData)
{
    if (hData == INVALID_HANDLE) return Plugin_Continue;
    
    ResetPack(hData);
    new iClient = ReadPackCell(hData);
    new iSlot = ReadPackCell(hData);
    g_hAttribute1059[iClient] = INVALID_HANDLE;
    
    if (!IsValidClient(iClient)) return Plugin_Continue;
    
    new Float:fDelay = GetClientAttribute(iClient, iSlot, ATTRIBUTE_MISS_CAUSE_DELAY);
    
    MakeSlotSleep(iClient, iSlot, fDelay, false);
    
    g_b1059LastWasMiss[iClient] = true;
    
    //PrintToChat(iClient, "Sleep for %.1f", fDelay);
    
    return Plugin_Continue;
}