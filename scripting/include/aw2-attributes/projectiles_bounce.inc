#define ATTRIBUTE_PROJECTILES_BOUNCE        1040

new g_iProjectileBounces[MAX_EDICTS+1] = 0;

Attribute_1040_EntityCreated(iEntity)
{
    g_iProjectileBounces[iEntity] = 0;
}

public Action:Attribute_1040_PStartTouch(iEntity, iOther, iOwner, iSlot)
{
    if (!ClientHasAttribute(iOwner, iSlot, ATTRIBUTE_PROJECTILES_BOUNCE)) return Plugin_Continue;
    if (IsValidClient(iOther)) return Plugin_Continue;
    if (IsEntityBuilding(iOther)) return Plugin_Continue;
    
    new iTotal = RoundFloat(GetClientAttribute(iOwner, iSlot, ATTRIBUTE_PROJECTILES_BOUNCE));
    if (g_iProjectileBounces[iEntity] >= iTotal) return Plugin_Continue;
    #if defined ENABLE_SDKHOOKS
    SDKHook(iEntity, SDKHook_Touch, Attribute_1040_OnTouchBounce);
    #endif
    g_iProjectileBounces[iEntity]++;
    
    //PrintToChat(iOwner, "Projectile bounce");
    return Plugin_Handled;
}

public Action:Attribute_1040_OnTouchBounce(iEntity, iOther) {    
    decl Float:vOrigin[3];
    GetEntPropVector(iEntity, Prop_Data, "m_vecOrigin", vOrigin);
    
    decl Float:vAngles[3];
    GetEntPropVector(iEntity, Prop_Data, "m_angRotation", vAngles);
    
    decl Float:vVelocity[3];
    GetEntPropVector(iEntity, Prop_Data, "m_vecAbsVelocity", vVelocity);
    
    new Handle:hTrace = TR_TraceRayFilterEx(vOrigin, vAngles, MASK_SHOT, RayType_Infinite, TraceRayDontHitEntity, iEntity);
    
    if(!TR_DidHit(hTrace))
    {
        CloseHandle(hTrace);
        return Plugin_Continue;
    }
    
    decl Float:vNormal[3];
    TR_GetPlaneNormal(hTrace, vNormal);
    
    CloseHandle(hTrace);
    
    new Float:dotProduct = GetVectorDotProduct(vNormal, vVelocity);
    
    ScaleVector(vNormal, dotProduct);
    ScaleVector(vNormal, 2.0);
    
    decl Float:vBounceVec[3];
    SubtractVectors(vVelocity, vNormal, vBounceVec);
    
    decl Float:vNewAngles[3];
    GetVectorAngles(vBounceVec, vNewAngles);
    
    TeleportEntity(iEntity, NULL_VECTOR, vNewAngles, vBounceVec);

    #if defined ENABLE_SDKHOOKS
    SDKUnhook(iEntity, SDKHook_Touch, Attribute_1040_OnTouchBounce);
    #endif
    return Plugin_Handled;
}