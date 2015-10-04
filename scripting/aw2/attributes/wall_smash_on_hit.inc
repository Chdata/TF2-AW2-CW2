#define ATTRIBUTE_WALL_SMASH_ON_HIT         1012

new bool:g_bAttWallSmash[MAXPLAYERS+1] = false;
new g_iAttWallSmashAttacker[MAXPLAYERS+1] = false;

public Action:Attribute_1012_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_WALL_SMASH_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    decl Float:fVelocity[3];
    decl Float:fAngle[3];
    GetClientEyeAngles(iAttacker, fAngle);
    AnglesToVelocity(fAngle, fVelocity, 230.0);
    fVelocity[2] = 270.0;
    
    TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, fVelocity);
    
    g_bAttWallSmash[iVictim] = true;
    g_iAttWallSmashAttacker[iVictim] = iAttacker;
    
    return Plugin_Continue;
}

Attribute_1012_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!g_bAttWallSmash[iClient]) return iButtons;
    if (OnGround(iClient))
    {
        g_bAttWallSmash[iClient] = false;
        g_iAttWallSmashAttacker[iClient] = -1;
        return iButtons;
    }
    
    // Check if smashing into wall
    decl Float:vClientOrigin[3];
    decl Float:vAngles[3];
    decl Float:vVelocity[3];
    GetClientEyePosition(iClient, vClientOrigin);
    GetVelocity(iClient, vVelocity);
    
    new Float:fSpeed = GetVectorLength(vVelocity);
    
    if (fSpeed < 150.0) return iButtons;
    
    GetVectorAngles(vVelocity, vAngles);
    vAngles[0] = 0.0;
    TR_TraceRayFilter(vClientOrigin, vAngles, MASK_PLAYERSOLID_BRUSHONLY, RayType_Infinite, TraceRayDontHitEntity, iClient);
    
    if (!TR_DidHit()) return iButtons;
    
    new iAttacker = g_iAttWallSmashAttacker[iClient];
    new iDamage = 100;
    DealDamage(iClient, iDamage, iAttacker);
    EmitSoundToClient(iAttacker, SOUND_BONEBREAK);
    EmitSoundToAll(SOUND_BONEBREAK, iClient);
    
    g_bAttWallSmash[iClient] = false;
    g_iAttWallSmashAttacker[iClient] = -1;
    
    return iButtons;
}