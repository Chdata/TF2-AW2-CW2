#define ATTRIBUTE_PARTICLE_IMPACT           1145

public Action:Attribute_1145_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_PARTICLE_IMPACT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    decl Float:fAngles[3], Float:fVelocity[3], Float:fOrigin[3];
    GetClientEyePosition(iVictim, fOrigin);
    GetClientEyeAngles(iVictim, fAngles);
    AnglesToVelocity(fAngles, fVelocity, 250.0);
    
    new iParticle = CreateEntityByName("info_particle_system");
    TeleportEntity(iParticle, fOrigin, fAngles, fVelocity);
    new Float:Cond_Check = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_PARTICLE_IMPACT);
    if (Cond_Check <= 1.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_EXPLOSION_BUBBLES);
    }
    else if (Cond_Check == 2.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_EXPLOSION);
    }
    else if (Cond_Check == 3.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_FLASH);
    }
    else if (Cond_Check == 4.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_ZEUS);
    }
    else if (Cond_Check == 5.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_BISONIMPACT);
    }
    else if (Cond_Check == 6.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_ORBITING_SKULL);
    }
    else if (Cond_Check == 7.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_WUBWUB_BEAM);
    }
    else if (Cond_Check == 8.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_ZEUS_CRACKLE);
    }
    else if (Cond_Check == 9.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_POISON_GOOP);
    }
    else if (Cond_Check == 10.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_SNOWIMPACT);
    }
    else if (Cond_Check == 11.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_ELECTROCUTED);
    }
    else if (Cond_Check == 12.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_BISONSHOCK);
    }
    else if (Cond_Check == 13.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_GLOWINGBURST);
    }
    else if (Cond_Check == 14.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_PURPLE_FLAME_SMOG);
    }
    else if (Cond_Check == 15.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_EXPLOSION_SMOKE);
    }
    else if (Cond_Check >= 16.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_BUBBLESTREAM);
    }
    DispatchSpawn(iParticle);
    ActivateEntity(iParticle);
    AcceptEntityInput(iParticle, "start");
    SetVariantString("OnUser1 !self:Kill::8:-1");
    AcceptEntityInput(iParticle, "AddOutput");
    AcceptEntityInput(iParticle, "FireUser1");
    
    return Plugin_Changed;
}