#define ATTRIBUTE_DISORIENTATE_ON_HIT           1004

#define SOUND_1004_A                        "physics/surfaces/underwater_impact_bullet1.wav"
#define SOUND_1004_B                        "physics/surfaces/underwater_impact_bullet2.wav"
#define SOUND_1004_C                        "physics/surfaces/underwater_impact_bullet3.wav"

Attribute_1004_Precache()
{
    SuperPrecacheSound(SOUND_1004_A);
    SuperPrecacheSound(SOUND_1004_B);
    SuperPrecacheSound(SOUND_1004_C);
}

public Action:Attribute_1004_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (IsAfterDamage(iDamageType)) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DISORIENTATE_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (DamageWillKill(iVictim, fDamage)) return Plugin_Continue;
    
    new Float:vEyeAngles[3];
    new Float:fSpin = fDamage;
    if (fSpin > 40.0) fSpin = 40.0;
    
    if (fSpin <= 10.0) return Plugin_Continue;
    
    GetClientEyeAngles(iVictim, vEyeAngles);
    vEyeAngles[0] += GetRandomFloat(-1.0, 1.0) * fSpin * 0.6;
    vEyeAngles[1] += GetRandomFloat(-1.0, 1.0) * fSpin * 0.6;
    TeleportEntity(iVictim, NULL_VECTOR, vEyeAngles, NULL_VECTOR);
    
    decl String:strSound[PLATFORM_MAX_PATH];
    new iRandom = GetRandomInt(1,3);
    if (iRandom == 1) Format(strSound, sizeof(strSound), SOUND_1004_A);
    if (iRandom == 2) Format(strSound, sizeof(strSound), SOUND_1004_B);
    else Format(strSound, sizeof(strSound), SOUND_1004_C);
    
    EmitSoundToClient(iVictim, strSound, _, _, SNDLEVEL_SCREAMING);
    
    if (ShouldReveal(iVictim)) {
        EmitSoundToClient(iAttacker, strSound, iVictim, _, SNDLEVEL_TRAIN);
        decl Float:vPos[3];
        GetClientEyePosition(iVictim, vPos);
        vPos[2] += 2.0;
        TE_ParticleFromClient(iVictim, "hit_text", vPos);
    }
    
    return Plugin_Continue;
}