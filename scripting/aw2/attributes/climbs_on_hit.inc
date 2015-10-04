#define ATTRIBUTE_CLIMBS_ON_HIT         1002

Attribute_1002_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CLIMBS_ON_HIT)) return;
    
    decl Float:vEyePos[3];
    decl Float:vEyeAng[3];
    GetClientEyePosition(iClient, vEyePos);
    GetClientEyeAngles(iClient, vEyeAng);

    //Check for colliding entities
    TR_TraceRayFilter(vEyePos, vEyeAng, MASK_PLAYERSOLID, RayType_Infinite, TraceRayDontHitPlayers);
    if (!TR_DidHit(INVALID_HANDLE)) return;
    
    decl Float:vNormal[3];
    TR_GetPlaneNormal(INVALID_HANDLE, vNormal);
    GetVectorAngles(vNormal, vNormal);
    
    if (vNormal[0] >= 30.0 && vNormal[0] <= 330.0) return;
    if (vNormal[0] <= -30.0) return;

    decl Float:vEnd[3];
    TR_GetEndPosition(vEnd);
    new Float:fDistance = GetVectorDistance(vEyePos, vEnd);
    if (fDistance >= 100.0) return;
    
    new Float:vVelocity[3];
    GetVelocity(iClient, vVelocity);
    vVelocity[2] = 600.0;
    TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    
    MakeSlotSleep(iClient, iSlot, 1.3, false);
}