#define ATTRIBUTE_DESPERATE_KATANA         1179

new g_iDesperateMode[MAXPLAYERS+1] = 0;
new g_iDesperateTarget[MAXPLAYERS+1] = 0;
new Float:g_fDesperateAttackAngle[MAXPLAYERS+1];
new Float:g_fDesperateSpecialTime[MAXPLAYERS+1] = 0.0;
new Float:g_fDesperateSpecialTime2[MAXPLAYERS+1] = 0.0;

Attribute_1179_Precache()
{
    PrecacheParticle("bomibomicon_ring");
}

Attribute_1179_OnInventory(iClient, &iSlot)
{
    Attribute_1179_Cancel(iClient);
}

Attribute_1179_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DESPERATE_KATANA)) return;
    
    if (OnGround(iClient))
    {
        decl Float:vAngles[3], Float:vVelocity[3];
        GetClientEyeAngles(iClient, vAngles);
        vAngles[0] = 0.0;
        vAngles[2] = 0.0;
        g_fDesperateAttackAngle[iClient] = vAngles[1];
        
        AnglesToVelocity(vAngles, vVelocity, 450.0);
        TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    }
}

public Action:Attribute_1179_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    // don't hurt them during special
    if (g_iDesperateTarget[iAttacker] > 0 && g_iDesperateTarget[iAttacker] != iVictim)
    {
        fDamage = 0.0;
        return Plugin_Changed;
    }
    if (g_iDesperateTarget[iVictim] > 0 && g_iDesperateTarget[iVictim] != iAttacker)
    {
        fDamage = 0.0;
        return Plugin_Changed;
    }
    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DESPERATE_KATANA)) return Plugin_Continue;
    if (IsAfterDamage(iDamageType)) return Plugin_Continue;
    
    if (g_iDesperateTarget[iAttacker] == iVictim)
    {
        fDamage *= 4.0;
        Attribute_1179_Cancel(iAttacker);
        return Plugin_Changed;
    }
    
    new Float:vAngles[3] = {0.0, 0.0, 0.0};
    vAngles[1] = g_fDesperateAttackAngle[iAttacker];
    
    decl Float:vVelocity[3];
    AnglesToVelocity(vAngles, vVelocity, 450.0);
    TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vVelocity);
    
    if (DamageWillKill(iVictim, fDamage))
    {
        Attribute_1179_SpecialAttack(iAttacker, iVictim);
        fDamage = 0.0;
        return Plugin_Changed;
    }
    
    return Plugin_Continue;
}

Attribute_1179_SpecialAttack(iClient, iVictim)
{
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_DESPERATE_KATANA)) return;
    if (g_fDesperateSpecialTime[iClient] > 0.0) return;

    Attribute_1179_Cancel(iClient);
    
    g_fDesperateSpecialTime[iClient] = GetEngineTime();
    g_iDesperateTarget[iClient] = iVictim;
    g_iDesperateMode[iClient] = 0;
    
    if (GetClientCeilingDistance(iClient) <= 8.0 || GetClientCeilingDistance(iVictim) <= 8.0) g_iDesperateMode[iClient] = 1;
    
    if (g_iDesperateMode[iClient] == 1)
    {
        new Float:vVelocity[3];
        decl Float:vOrigin[3], Float:vOriginTarget[3];
        GetClientAbsOrigin(iClient, vOrigin);
        GetClientAbsOrigin(iVictim, vOriginTarget);
        SubtractVectors(vOriginTarget, vOrigin, vVelocity);
        NormalizeVector(vVelocity, vVelocity);
        ScaleVector(vVelocity, 500.0);
        if (OnGround(iVictim)) vVelocity[2] = 600.0;
        else vVelocity[2] = 300.0;
        
        TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vVelocity);
        ShowParticle("bomibomicon_ring", 2.0, vOriginTarget);
    }
    else
    {
        new Float:vVelocity[3];
        
        decl Float:vOrigin[3], Float:vOriginTarget[3];
        GetClientAbsOrigin(iClient, vOrigin);
        GetClientAbsOrigin(iVictim, vOriginTarget);
        SubtractVectors(vOrigin, vOriginTarget, vVelocity);
        NormalizeVector(vVelocity, vVelocity);
        ScaleVector(vVelocity, 100.0);
        vVelocity[2] = 900.0;
        
        TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
        ShowParticle("bomibomicon_ring", 2.0, vOrigin);
        
        vVelocity[0] *= -1.0;
        vVelocity[1] *= -1.0;
        TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vVelocity);
        ShowParticle("bomibomicon_ring", 2.0, vOriginTarget);
        
    }
    CloakIsHookToggle(iVictim, true);
    TF2_StunPlayer(iVictim, 2.0, 1.0, TF_STUNFLAGS_LOSERSTATE|TF_STUNFLAG_THIRDPERSON|TF_STUNFLAG_SLOWDOWN|TF_STUNFLAG_NOSOUNDOREFFECT|TF_STUNFLAG_LIMITMOVEMENT);
}

Attribute_1179_Cancel(iClient)
{
    if (g_fDesperateSpecialTime[iClient] > 0.0)
    {
        // reset
    }
    g_fDesperateSpecialTime[iClient] = 0.0;
    g_fDesperateSpecialTime2[iClient] = 0.0;
    g_iDesperateMode[iClient] = 0;
}

Attribute_1179_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    new Float:fTime = g_fDesperateSpecialTime[iClient];
    if (fTime <= 0.0 && OnGround(iClient)) g_iDesperateTarget[iClient] = 0;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_DESPERATE_KATANA)) return iButtons;
    if (g_fDesperateSpecialTime[iClient] <= 0.0) return iButtons;
    
    new Float:fTimeOld = g_fDesperateSpecialTime2[iClient];
    new iTarget = g_iDesperateTarget[iClient];
    new iMode = g_iDesperateMode[iClient];
    if (!IsValidClient(iTarget) || !IsPlayerAlive(iTarget))
    {
        Attribute_1179_Cancel(iClient);
        return iButtons;
    }
    
    if (GetEngineTime() >= fTime + 2.0)
    {
        Attribute_1179_Cancel(iClient);
        return iButtons;
    }
    else if (GetEngineTime() >= fTime + 1.0 && fTimeOld < fTime + 1.0)
    {
        TF2_AddCondition(iClient, TFCond_CritOnKill, 1.0);
        if (iMode == 1) TF2_AddCondition(iClient, TFCond_Charging, 0.7);
        decl Float:vOrigin[3], Float:vOriginTarget[3];
        GetClientAbsOrigin(iClient, vOrigin);
        GetClientAbsOrigin(iTarget, vOriginTarget);
        
        decl Float:vVelocity[3];
        SubtractVectors(vOriginTarget, vOrigin, vVelocity);
        NormalizeVector(vVelocity, vVelocity);
        ScaleVector(vVelocity, 400.0);
        if (iMode != 1) vVelocity[2] += 130.0;
        TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    }
    
    g_fDesperateSpecialTime2[iClient] = GetEngineTime();
    
    return iButtons;
}