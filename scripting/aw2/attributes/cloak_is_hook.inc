#define ATTRIBUTE_CLOAK_IS_HOOK         1039

new g_iCloakIsHook[MAXPLAYERS+1] = 0;
new Float:g_fCloakIsHookTime[MAXPLAYERS+1] = 0.0;
new Float:g_vCloakIsHookOrigin[MAXPLAYERS+1][3];

Attribute_1039_OnInventory(iClient, &iSlot)
{
    CloakIsHookToggle(iClient, true);
    g_iCloakIsHook[iClient] = 0;
}

Attributes_1039_Stop()
{
    for (new i = 1; i <= MaxClients; i++)
    {
        CloakIsHookToggle(i, true);
    }
}

CloakIsHookToggle(iClient, bool:bForceStop = false)
{
    if (!IsValidClient(iClient)) return;
    //PrintToChat(iClient, "CloakIsHookToggle");
    if (bForceStop && g_iCloakIsHook[iClient] != 1) return;
    if (g_iCloakIsHook[iClient] > 1) return;
    
    if (g_iCloakIsHook[iClient] > 0)
    {
        TF2_RemoveCondition(iClient, TFCond_Cloaked);
        g_iCloakIsHook[iClient] = 2;
        SetEntityMoveType(iClient, MOVETYPE_WALK);
        
        decl Float:vEyeAngles[3], Float:vVelocity[3];
        GetClientEyeAngles(iClient, vEyeAngles);
        AnglesToVelocity(vEyeAngles, vVelocity, 400.0);
        TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    }
    else
    {
        decl Float:vEyeAngles[3];
        GetClientEyeAngles(iClient, vEyeAngles);
        CloakIsHookInit(iClient, vEyeAngles);
    }
}

bool:CloakIsHookInit(iClient, Float:vAngles[3])
{
   // PrintToChat(iClient, "CloakIsHookInit");
    if (g_iCloakIsHook[iClient] == 1) return false;
    
    if (GetEntPropFloat(iClient, Prop_Send, "m_flCloakMeter") <= 5.0) return false;
    if (!GetClientViewTarget2(iClient, vAngles, g_vCloakIsHookOrigin[iClient], true)) return false;
    
    decl Float:vOrigin[3];
    GetClientAbsOrigin(iClient, vOrigin);
    // too far away
    if (GetVectorDistance(vOrigin, g_vCloakIsHookOrigin[iClient])/50.0 > 10.0) return false;
    if (g_vCloakIsHookOrigin[iClient][2] <= vOrigin[2]) return false;
    
    TF2_AddCondition(iClient, TFCond_Cloaked, 100.0);
    g_iCloakIsHook[iClient] = 1;
    g_fCloakIsHookTime[iClient] = GetEngineTime();
    return true;
}

Attribute_1039_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!IsPlayerAlive(iClient)) return iButtons;
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CLOAK_IS_HOOK)) return iButtons;
    
    // toggle ATTACK2
    new Float:fSpeed = GetEntPropFloat(iClient, Prop_Send, "m_flMaxspeed");
    if (iButtonsLast & IN_ATTACK2 != IN_ATTACK2 && iButtons & IN_ATTACK2 == IN_ATTACK2 && g_fCloakIsHookTime[iClient] < GetEngineTime() - 1.0 && fSpeed >= 5.0) CloakIsHookToggle(iClient);
    if (GetEntPropFloat(iClient, Prop_Send, "m_flCloakMeter") <= 0.0) CloakIsHookToggle(iClient, true);
    
    if (g_iCloakIsHook[iClient] > 1 && OnGround(iClient)) g_iCloakIsHook[iClient] = 0;
    
    if (g_iCloakIsHook[iClient] != 1)
    {
        //ModifyCloak(iClient, 0.05);
        return iButtons;
    }
    
    //ModifyCloak(iClient, -0.01);
    if (GetEntityMoveType(iClient) == MOVETYPE_NONE) return iButtons;
    
    decl Float:vOrigin[3];
    GetClientAbsOrigin(iClient, vOrigin);
    
    decl Float:vVelocity[3];
    SubtractVectors(g_vCloakIsHookOrigin[iClient], vOrigin, vVelocity);
    NormalizeVector(vVelocity, vVelocity);
    ScaleVector(vVelocity, 900.0);
    if (OnGround(iClient) && vVelocity[2] < 300.0 && vVelocity[2] > 0) vVelocity[2] = 300.0;
    else vVelocity[2] += 20.0;
    TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    
    decl Float:vOriginEye[3];
    GetClientEyePosition(iClient, vOriginEye);
    vOrigin[2] = (vOriginEye[2] - vOrigin[2])/2.0 + vOrigin[2];
    new Float:fDistance = GetVectorDistance(vOrigin, g_vCloakIsHookOrigin[iClient]) / 50.0;
    if (fDistance >= 1.1 && g_fCloakIsHookTime[iClient] >= GetEngineTime() - 0.5)
    {
        ClientRope(iClient, g_vCloakIsHookOrigin[iClient]);
    }
    else
    {
        SetEntityMoveType(iClient, MOVETYPE_NONE);
    }
    
    return iButtons;
}