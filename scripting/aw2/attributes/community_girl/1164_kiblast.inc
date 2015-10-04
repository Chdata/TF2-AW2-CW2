#define ATTRIBUTE_KI_BLAST         1164

public Attribute_1164_Init()
{
    AddRecharge(ATTRIBUTE_KI_BLAST, "Ki", _, _, _, false);
}

public Action:Attribute_1164_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    //1.0 = Heavy taunt, where we only want fists to generate Ki. 2.0 = Pyro taunt, where any attack can generate Ki, but at a slower 
    if (TF2_GetPlayerClass(iAttacker) == TFClass_Heavy)
        {
        if (GetClientSlot(iAttacker) == 2)
            {
                new Float:fGaugeKi = fDamage *0.25;
                AddClientRecharge(iAttacker, ATTRIBUTE_KI_BLAST, fGaugeKi);
            }
        }
    else if (TF2_GetPlayerClass(iAttacker) == TFClass_Pyro)
    {
        new Float:fGaugeKi = fDamage *0.18;
        AddClientRecharge(iAttacker, ATTRIBUTE_KI_BLAST, fGaugeKi);
    }
    
    return Plugin_Continue;
}

public Attribute_1164_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Taunting) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_KI_BLAST)) return;
    if (GetClientRecharge(iClient, ATTRIBUTE_KI_BLAST) < 100.0) return;
        
    //It's hard for me to get the exact time when the Pyro/Heavy have executed their taunt's attack. The full taunt duration is 3.0 sec, but from the videos I've been studying, Heavy POWs at 2.5 sec, Pyro Hadokens at 2.3.
    
    new Float:fTime1164 = GetClientAttribute(iClient, _, ATTRIBUTE_KI_BLAST);
    CreateTimer(fTime1164, Attribute_Pow, iClient);  
}

public Action:Attribute_Pow(Handle:hTimer, any:iClient) 
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_KI_BLAST)) return;
    
    decl Float:fAngles[3], Float:fVelocity[3], Float:fOrigin[3];
        
    if (TF2_GetPlayerClass(iClient) == TFClass_Heavy)
    {
    AddClientRecharge(iClient, ATTRIBUTE_KI_BLAST, -100.0);
    
    new iEntity = CreateEntityByName("tf_projectile_energy_ring");
    if (IsValidEdict(iEntity)) {
        SetEntPropEnt(iEntity, Prop_Data, "m_hOwnerEntity", iClient);
        DispatchSpawn(iEntity);
        
        //Heavy finger blast does about crocket level damage.
        
        SetEntityRenderMode(iEntity, RENDER_TRANSCOLOR);
        SetEntityRenderColor(iEntity, 150, 150, 150, 75);
                
        GetClientEyePosition(iClient, fOrigin);
        GetClientEyeAngles(iClient, fAngles);
        AnglesToVelocity(fAngles, fVelocity, 600.0);
        new Float:fKiBlast = GetEntPropFloat(iEntity, Prop_Send, "m_flDamage") * 2.5;
        SetEntPropFloat(iEntity, Prop_Send, "m_flDamage", fKiBlast);
        SetEntPropFloat(iEntity, Prop_Send, "m_flModelWidthScale",1.1);
        
        TeleportEntity(iEntity, fOrigin, fAngles, fVelocity);
        AttachParticle(iEntity, PARTICLE_ELECTRICITY);
        AttachParticle(iEntity, PARTICLE_SPIRITBALL);
    }
    }
    
    else if (TF2_GetPlayerClass(iClient) == TFClass_Pyro)
    {
    AddClientRecharge(iClient, ATTRIBUTE_KI_BLAST, -100.0);
    
    //Hadoken does around 200 damage with an area of effect 15% larger than standard rocket.
    
    new iEntity = CreateEntityByName("tf_projectile_energy_ring");
    if (IsValidEdict(iEntity)) {
        SetEntPropEnt(iEntity, Prop_Data, "m_hOwnerEntity", iClient);
        DispatchSpawn(iEntity);
        
        SetEntityRenderMode(iEntity, RENDER_TRANSCOLOR);
        SetEntityRenderColor(iEntity, 255, 75, 75, 75);
        
        GetClientEyePosition(iClient, fOrigin);
        GetClientEyeAngles(iClient, fAngles);
        AnglesToVelocity(fAngles, fVelocity, 600.0);
        new Float:fKiBlast = GetEntPropFloat(iEntity, Prop_Send, "m_flDamage") * 2.0;
        GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
        ScaleVector(fVelocity, 1.2);
        SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
        SetEntPropFloat(iEntity, Prop_Send, "m_DmgRadius", 165.6);
        SetEntPropFloat(iEntity, Prop_Send, "m_flDamage", fKiBlast);
        SetEntPropFloat(iEntity, Prop_Send, "m_flModelWidthScale",1.8);
        
        TeleportEntity(iEntity, fOrigin, fAngles, fVelocity);
        AttachParticle(iEntity, PARTICLE_HADOKEN_TRAIL);
        AttachParticle(iEntity, PARTICLE_HADOKEN);
    }
    }
}