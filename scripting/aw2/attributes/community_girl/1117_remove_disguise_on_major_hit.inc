#define ATTRIBUTE_REMOVE_DISGUISE_ON_MAJOR_HIT         1117

public Action:Attribute_1117_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_REMOVE_DISGUISE_ON_MAJOR_HIT)) return Plugin_Continue;
    if (fDamage <= GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_REMOVE_DISGUISE_ON_MAJOR_HIT)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    
    decl Float:vOrigin[3];
    GetClientEyePosition(iVictim, vOrigin);
    vOrigin[2] += 2.0;
    if(TF2_IsPlayerInCondition(iVictim, TFCond_Disguised)) {
    TF2_RemoveCondition(iVictim, TFCond_Disguised);
    new iCheck = GetClientTeam(iVictim);
    if (iCheck == 2) {
    TE_ParticleFromClient(iVictim, PARTICLE_SPY_DISGUISE_R, vOrigin);
    }
    if (iCheck == 3) {
    TE_ParticleFromClient(iVictim, PARTICLE_SPY_DISGUISE_B, vOrigin);
    }
    }
    return Plugin_Continue;
}