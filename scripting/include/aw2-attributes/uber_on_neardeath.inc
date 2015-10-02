#define ATTRIBUTE_UBER_ON_NEARDEATH         1003

#define UBER_ON_NEARDEATH_DURATION          5.0

new Float:g_fNeardeathUber[MAXPLAYERS+1] = 0.0;
new g_AchievementShockerUnion[MAXPLAYERS+1] = 0;

public Attribute_1003_Init()
{
    AddRecharge(ATTRIBUTE_UBER_ON_NEARDEATH, "Electroshock");
}

Attribute_1003_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_UBER_ON_NEARDEATH)) return;
    g_fNeardeathUber[iClient] = 0.0;
    g_AchievementShockerUnion[iClient] = 0;
}

public Action:Attribute_1003_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    // This is the part where we add to his Electroshock
    if (iVictim != iAttacker && IsValidClient(iAttacker) && ClientHasAttribute(iAttacker, _, ATTRIBUTE_UBER_ON_NEARDEATH))
    {
        new Float:fValue = fDamage * GetClientAttribute(iAttacker, _, ATTRIBUTE_UBER_ON_NEARDEATH) * 0.1;
        AddClientRecharge(iAttacker, ATTRIBUTE_UBER_ON_NEARDEATH, fValue);
        //added for visual distinction
        new weaponentity1103 = GetEntPropEnt(iAttacker, Prop_Send, "m_hActiveWeapon");
        AttachParticle(weaponentity1103, PARTICLE_ELECTRICITY, 1.0);
    }

    // This is the revival shock part
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (!ClientHasAttribute(iVictim, _, ATTRIBUTE_UBER_ON_NEARDEATH)) return Plugin_Continue;
    if (!IsRechargeMax(iVictim, ATTRIBUTE_UBER_ON_NEARDEATH)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (!DamageWillKill(iVictim, fDamage, true)) return Plugin_Continue;
    
    g_AchievementShockerUnion[iVictim] += 1;
    if (g_AchievementShockerUnion[iVictim] == 2) SlagInv_AddAchievementProgress(iVictim, "aw2_shockerunion");
    EmitSoundToAll(SOUND_VO_HEAVY_I_LIVE, iVictim, _, SNDLEVEL_SCREAMING);
    EmitSoundToClient(iVictim, SOUND_UBERCHARGE, _, _, SNDLEVEL_SCREAMING);
    TF2_AddCondition(iVictim, TFCond_Ubercharged, UBER_ON_NEARDEATH_DURATION);
    SetWeaponAmmo(iVictim, 0, 0);
    SetWeaponAmmo(iVictim, 1, 0);
    SetClientSlot(iVictim, 2);
    
    fDamage = 0.0;
    SetEntityHealth(iVictim, 1);
    SetClientRecharge(iVictim, ATTRIBUTE_UBER_ON_NEARDEATH, 0.0);
    
    g_fNeardeathUber[iVictim] = GetEngineTime();
    
    decl Float:fAngles[3], Float:fVelocity[3], Float:fOrigin[3];
    GetClientEyePosition(iVictim, fOrigin);
    GetClientEyeAngles(iVictim, fAngles);
    AnglesToVelocity(fAngles, fVelocity, 250.0);
    
    AttachParticle(iVictim, PARTICLE_ZEUS, 1.5);
    
    fOrigin[0] += 10.0;
    fOrigin[1] += 5.0;
    fOrigin[2] += 5.0;
    
    AttachParticle(iVictim, PARTICLE_ZEUS, 1.5);
    
    fOrigin[0] -= 15.0;
    fOrigin[1] -= 10.0;
    fOrigin[2] -= 10.0;
    
    AttachParticle(iVictim, PARTICLE_ZEUS, 1.5);
    
    return Plugin_Changed;
}

Attribute_1003_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_UBER_ON_NEARDEATH) && g_fNeardeathUber[iClient] >= GetEngineTime() - UBER_ON_NEARDEATH_DURATION)
    {
        SetWeaponAmmo(iClient, 0, 0);
        SetWeaponAmmo(iClient, 1, 0);
        SetEntityHealth(iClient, 1);
    }
    
    return iButtons;
}