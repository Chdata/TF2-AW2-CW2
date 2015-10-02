#define ATTRIBUTE_DEATH_IS_BRUTAL         1180

Attribute_1180_Precache()
{    
    PrecacheParticle("water_blood_impact_red_01");
    PrecacheParticle("blood_impact_red_01");
    PrecacheParticle("blood_trail_red_01_goop");
    PrecacheParticle("env_sawblood");
    PrecacheParticle("blood_decap");
}

Attribute_1180_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
    if (!IsValidClient(iAttacker)) return;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DEATH_IS_BRUTAL)) return;
    if (iAttacker == iClient) return;
    
    decl Float:vOrigin[3];
    GetClientAbsOrigin(iClient, vOrigin);
    
    Attribute_1180_RandomParticle("water_blood_impact_red_01", vOrigin);
    Attribute_1180_RandomParticle("blood_impact_red_01", vOrigin);
    Attribute_1180_RandomParticle("blood_trail_red_01_goop", vOrigin);
    Attribute_1180_RandomParticle("env_sawblood", vOrigin);
    Attribute_1180_RandomParticle("blood_decap", vOrigin);
    
    Attribute_1180_Gib(iClient);
}

Attribute_1180_RandomParticle(String:strName[], Float:vOrigin[3])
{
    decl Float:vOffset[3], Float:vNewOrigin[3];
    
    new iRandom = GetRandomInt(2,15);
    for (new i = 0; i < iRandom; i++)
    {
        vOffset[0] += GetRandomFloat(-200.0, 200.0);
        vOffset[1] += GetRandomFloat(-200.0, 200.0);
        vOffset[2] += GetRandomFloat(-200.0, 200.0);
        AddVectors(vOrigin, vOffset, vNewOrigin);
        
        decl Float:vAngles[3];
        vAngles[0] = GetRandomFloat(-180.0, 180.0);
        vAngles[1] = GetRandomFloat(-180.0, 180.0);
        vAngles[2] = GetRandomFloat(-180.0, 180.0);
        
        ShowParticle(strName, 10.0, vNewOrigin, vAngles);
    }
}

Attribute_1180_Gib(iClient)
{
    new iEntity = CreateEntityByName("tf_ragdoll");
    if (iEntity <= 0) return;
    
    decl Float:vOrigin[3];
    GetClientAbsOrigin(iClient, vOrigin);
    
    SetEntPropVector(iEntity, Prop_Send, "m_vecRagdollOrigin", vOrigin); 
    SetEntProp(iEntity, Prop_Send, "m_iPlayerIndex", iClient); 
    SetEntPropVector(iEntity, Prop_Send, "m_vecForce", NULL_VECTOR);
    SetEntPropVector(iEntity, Prop_Send, "m_vecRagdollVelocity", NULL_VECTOR);
    SetEntProp(iEntity, Prop_Send, "m_bGib", 1);

    DispatchSpawn(iEntity);
    
    CreateTimer(15.0, Attribute_1180_RemoveGibs, iEntity);
}

public Action:Attribute_1180_RemoveGibs(Handle:Timer, any:iEntity)
{
	if(!IsClassname(iEntity, "tf_ragdoll")) return;

	AcceptEntityInput(iEntity, "kill");
}