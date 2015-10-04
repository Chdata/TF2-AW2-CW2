#define ATTRIBUTE_COMBO_CLAW         1090

new g_iClawCombo[MAXPLAYERS+1] = 0;
new Float:g_fClawComboLast[MAXPLAYERS+1] = 0.0;
new Float:g_fClawComboSoundLast[MAXPLAYERS+1] = 0.0;
new Handle:g_hClawCombo[MAXPLAYERS+1] = INVALID_HANDLE;

public Action:Attribute_1090_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_COMBO_CLAW)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (GetEngineTime() >= g_fClawComboLast[iAttacker] + 0.7)
    {
        g_iClawCombo[iAttacker] = 0;
    }
    
    g_fClawComboLast[iAttacker] = GetEngineTime();
    
    if (g_iClawCombo[iAttacker] == 0)
    {
        if (GetEngineTime() >= g_fClawComboSoundLast[iAttacker] + 5.0)
        {
            g_fClawComboSoundLast[iAttacker] = GetEngineTime();
            EmitSoundToAll(SOUND_STABBY, iAttacker);
            //EmitSoundToClient(iAttacker, SOUND_STABBY);
            //if (IsValidClient(iVictim)) EmitSoundToClient(iVictim, SOUND_STABBY);
        }
    }
    
    if (GetEngineTime() >= g_fClawComboSoundLast[iAttacker] + 1.5)
    {
        EmitSoundToClient(iAttacker, SOUND_HORROR_BELL);
    }
    
    if (g_iClawCombo[iAttacker] >= 2)
    {
        iDamageType = TF_DMG_MELEE_CRIT;
        fDamage = 500.0;
        g_iClawCombo[iAttacker] = 0;
        if (g_hClawCombo[iAttacker] != INVALID_HANDLE) CloseHandle(g_hClawCombo[iAttacker]);
        return Plugin_Changed;
    }
    
    g_iClawCombo[iAttacker]++;
    
    return Plugin_Continue;
}
