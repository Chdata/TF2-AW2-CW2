#define ATTRIBUTE_AOEHEAL        1157

new Float:g_fCooldown1157[MAXPLAYERS+1] = 0.0;
new bool:g_bIsAOEHealing1157[MAXPLAYERS+1] = false;
new g_iHealCount1157[MAXPLAYERS+1] = 0;
new g_iTeam1157[MAXPLAYERS+1] = 0;
new Float:g_f1157Time[MAXPLAYERS+1] = 0.0;

Attribute_1157_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_AOEHEAL)) return;
    
    g_f1157Time[iClient] = GetClientAttribute(iClient, iSlot, ATTRIBUTE_AOEHEAL);   
    g_iTeam1157[iClient] = GetClientTeam(iClient);
}

Attribute_1157_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!IsValidClient(iClient)) return iButtons;
    
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_AOEHEAL) && (iButtons & IN_ATTACK2 == IN_ATTACK2))
    {
    new Float:fUber1157 = TF2_GetPlayerUberLevel(iClient);
    if (GetEngineTime() >= g_fCooldown1157[iClient] + g_f1157Time[iClient]) {
    if (fUber1157 >= 20.0) {
    fUber1157 -= 20.0;
    TF2_SetPlayerUberLevel(iClient, fUber1157);
    if (g_iTeam1157[iClient] == 2) {
    AttachParticle(iClient, PARTICLE_MEDIC_HEAL_AURA_R, g_f1157Time[iClient]);
    }
    else if (g_iTeam1157[iClient] == 3) {
    AttachParticle(iClient, PARTICLE_MEDIC_HEAL_AURA_B, g_f1157Time[iClient]);
    }
    EmitSoundToAll(SOUND_HEALAOE, iClient);
    EmitSoundToAll(SOUND_HEALAOE2, iClient);
    g_bIsAOEHealing1157[iClient] = true;
    g_fCooldown1157[iClient] = GetEngineTime();
    }
    }
    
    if (g_bIsAOEHealing1157[iClient]) {
    
    decl Float:vClientPos[3];
    GetClientAbsOrigin(iClient, vClientPos);
    decl Float:vVictimPos[3];
    new Float:fDistance;
    g_iHealCount1157[iClient]++;
    if (g_iHealCount1157[iClient] >= 30) {
    g_iHealCount1157[iClient] = 0;
    for (new iVictim = 0; iVictim <= MaxClients; iVictim++) {
        if (IsValidClient(iVictim) && IsPlayerAlive(iVictim) && g_iTeam1157[iClient] == GetClientTeam(iVictim)) {
            GetClientAbsOrigin(iVictim, vVictimPos);
            fDistance = GetVectorDistance(vVictimPos, vClientPos);
            if (fDistance <= 380.0) {
            new iHeal = 7;
            new iHealth = GetClientHealth(iVictim);
            iHealth += iHeal;
            new iOverHeal = GetClientMaxOverHeal(iVictim);
            if (iHealth > iOverHeal) iHealth = iOverHeal;
            SetEntityHealth(iVictim, iHealth);
            
            if (g_iTeam1157[iClient] == 2) {
            AttachParticle(iVictim, PARTICLE_HEALED_R, 0.5);
            }
            else if (g_iTeam1157[iClient] == 3) {
            AttachParticle(iVictim, PARTICLE_HEALED_B, 0.5);
            }
            }
        }
    }
    }
    }
    }
    
    if (g_bIsAOEHealing1157[iClient]) {
    if (GetEngineTime() >= g_fCooldown1157[iClient] + g_f1157Time[iClient]) {
    g_bIsAOEHealing1157[iClient] = false;
    }
    }
    
    return iButtons;
}