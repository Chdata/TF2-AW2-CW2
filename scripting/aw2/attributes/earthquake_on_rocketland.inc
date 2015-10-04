#define ATTRIBUTE_EARTHQUAKE_ON_ROCKETLAND          1026

#define ATTRIBUTE_1026_DISTANCE_LIMIT               600.0
#define ATTRIBUTE_1026_PUSHSCALE                    0.03
//#define ATTRIBUTE_1026_PUSHMAX                      3.0
#define ATTRIBUTE_1026_COOLDOWN                     3.5

new Float:g_f1026LastLand[MAXPLAYERS+1] = 0.0;

Attribute_1026_RocketJumpLand(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_EARTHQUAKE_ON_ROCKETLAND)) return;

    new Float:fPushMax = GetClientAttribute(iClient, iSlot, ATTRIBUTE_EARTHQUAKE_ON_ROCKETLAND);
    
    new Float:fDistance;
    
    decl Float:vClientPos[3];
    GetClientAbsOrigin(iClient, vClientPos);
    decl Float:vVictimPos[3];
    decl Float:vPush[3];
    
    new iTeam = GetClientTeam(iClient);
    
    EmitSoundFromOrigin(SOUND_EXPLOSION_BIG, vClientPos);
    TE_SetupExplosion(vClientPos, g_iExplosionSprite, 10.0, 1, 0, 0, 750);
    TE_SendToAll();
    TE_SetupBeamRingPoint(vClientPos, 10.0, ATTRIBUTE_1026_DISTANCE_LIMIT, g_iWhite, g_iHaloSprite, 0, 10, 0.2, 10.0, 0.5, g_iTeamColorSoft[iTeam], 50, 0);
    TE_SendToAll();
    
    Shake(iClient);
    
    for (new iVictim = 0; iVictim <= MaxClients; iVictim++) {
        if (IsValidClient(iVictim) && IsPlayerAlive(iVictim) && iTeam != GetClientTeam(iVictim) && OnGround(iVictim)) {
            GetClientAbsOrigin(iVictim, vVictimPos);
            fDistance = GetVectorDistance(vVictimPos, vClientPos);
            if (fDistance <= ATTRIBUTE_1026_DISTANCE_LIMIT) {
                if (GetEngineTime() <= g_f1026LastLand[iClient] + ATTRIBUTE_1026_COOLDOWN) return;
                SubtractVectors(vVictimPos, vClientPos, vPush);
                new Float:fPushScale = (ATTRIBUTE_1026_DISTANCE_LIMIT - fDistance)*ATTRIBUTE_1026_PUSHSCALE;
                //if (fPushScale > ATTRIBUTE_1026_PUSHMAX) fPushScale = ATTRIBUTE_1026_PUSHMAX;
                if (fPushScale > fPushMax) fPushScale = fPushMax;
                ScaleVector(vPush, fPushScale);
                Shake(iVictim);
                if (vPush[2] < 400.0) vPush[2] = 400.0;
                TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vPush);
		g_f1026LastLand[iClient] = GetEngineTime();
            }
        }
    }
}
