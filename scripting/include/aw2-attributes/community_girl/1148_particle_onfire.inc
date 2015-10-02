#define ATTRIBUTE_PARTICLE_ONFIRE      1148

Attribute_1148_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_PARTICLE_ONFIRE)) return;
         
    decl Float:fAngles[3], Float:fVelocity[3], Float:fOrigin[3];
    GetClientEyePosition(iClient, fOrigin);
    GetClientEyeAngles(iClient, fAngles);
    AnglesToVelocity(fAngles, fVelocity, 350.0);
    
    
    // This particle creation code is unnecessary. There is already a function for it in misc.inc
    new iParticle = CreateEntityByName("info_particle_system");
    TeleportEntity(iParticle, fOrigin, fAngles, fVelocity);
    new Float:Cond_Check = GetClientAttribute(iClient, iSlot, ATTRIBUTE_PARTICLE_ONFIRE);
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
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_BLOODIMPACT);
    }
    else if (Cond_Check == 4.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_ZEUS);
    }
    else if (Cond_Check == 5.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_FLASH);
    }
    else if (Cond_Check == 6.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_ALT_FIRESTREAM);
    }
    else if (Cond_Check == 7.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_WUBWUB_BEAM);
    }
    else if (Cond_Check == 8.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_DRAW_LASER_SIGHT);
    }
    else if (Cond_Check == 9.0)
    {
    DispatchKeyValue(iParticle, "effect_name", PARTICLE_MUSKET_FLASH);
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
}