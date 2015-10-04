#define ATTRIBUTE_SPREADFLARE		  1156

Attribute_1156_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SPREADFLARE)) return;
    if (!IsValidEdict(iEntity)) return;
    
    EntIndexToEntRef(iEntity);
    new Float:fTime1156 = GetClientAttribute(iClient, iSlot, ATTRIBUTE_SPREADFLARE);
    CreateTimer(fTime1156, Create_Flares1156, iEntity);
    fTime1156 += 0.1;
    CreateTimer(fTime1156, Remove_Flare1156, iEntity);
    
}

public Action:Remove_Flare1156(Handle:hTimer, any:iEntRef) 
{
    new iEntity = EntRefToEntIndex(iEntRef);
    if (!IsValidEdict(iEntity)) return;
    
    RemoveEdict(iEntity);
}

public Action:Create_Flares1156(Handle:hTimer, any:iEntRef) 
{
    new iEntity = EntRefToEntIndex(iEntRef);
    if (!IsValidEdict(iEntity)) return;

    new Float:fOrigin[3];
    new Float:fVelocity[3];
    new Float:fRotation[3];
    GetEntPropVector(iEntity, Prop_Data, "m_vecOrigin", fOrigin);
    GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
    GetEntPropVector(iEntity, Prop_Data, "m_angRotation", fRotation);

    new iOwner = GetEntProp(iEntity, Prop_Send, "m_hOwnerEntity");
    new Float:fDamageFlare = GetEntPropFloat(iEntity, Prop_Send, "m_flDamage");
    fDamageFlare *= 0.5;
    
    new iEntity2 = CreateEntityByName("tf_projectile_flare");
    if (IsValidEdict(iEntity2)) 
    {
        DispatchKeyValue(iEntity2, "model", "models/weapons/w_models/w_flaregun_shell.mdl");
        ScaleVector(fVelocity, 0.5);
        fOrigin[0] += 25.0;
        fOrigin[1] += 20.0;
        fOrigin[2] -= 15.0;
        fRotation[0] += 45.0;
        fRotation[1] += 45.0;
        SetEntPropVector(iEntity2, Prop_Send, "m_vecVelocity", fVelocity);

        GetEntPropVector(iEntity2, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 1.5);
        SetEntPropVector(iEntity2, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity2, Prop_Send, "m_flDamage", fDamageFlare);
        SetEntProp(iEntity2, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntPropFloat(iEntity2, Prop_Send, "m_flModelWidthScale",0.5);
        DispatchSpawn(iEntity2);
        TeleportEntity(iEntity2, fOrigin, fRotation, fVelocity);        
    }
    new iEntity3 = CreateEntityByName("tf_projectile_flare");
    if (IsValidEdict(iEntity3)) 
    {
        DispatchKeyValue(iEntity3, "model", "models/weapons/w_models/w_flaregun_shell.mdl");
        ScaleVector(fVelocity, 0.55);
        fOrigin[0] -= 50.0;
        fOrigin[1] -= 40.0;
        fOrigin[2] += 30.0;
        fRotation[0] += 45.0;
        fRotation[1] -= 90.0;
        SetEntPropVector(iEntity3, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity3, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 1.5);
        SetEntPropVector(iEntity3, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity3, Prop_Send, "m_flDamage", fDamageFlare);
        SetEntProp(iEntity3, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntPropFloat(iEntity3, Prop_Send, "m_flModelWidthScale",0.5);
        DispatchSpawn(iEntity3);
        TeleportEntity(iEntity3, fOrigin, fRotation, fVelocity);
    }
    new iEntity4 = CreateEntityByName("tf_projectile_flare");
    if (IsValidEdict(iEntity4)) 
    {
        DispatchKeyValue(iEntity4, "model", "models/weapons/w_models/w_flaregun_shell.mdl");
        ScaleVector(fVelocity, 0.45);
        fOrigin[0] += 25.0;
        fOrigin[1] -= 20.0;
        fOrigin[2] += 15.0;
        fRotation[0] -= 135.0;
        fRotation[1] += 45.0;
        SetEntPropVector(iEntity4, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity4, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 1.5);
        SetEntPropVector(iEntity4, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity4, Prop_Send, "m_flDamage", fDamageFlare);
        SetEntProp(iEntity4, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntPropFloat(iEntity4, Prop_Send, "m_flModelWidthScale",0.5);
        DispatchSpawn(iEntity4);
        TeleportEntity(iEntity4, fOrigin, fRotation, fVelocity);
    }
    new iEntity5 = CreateEntityByName("tf_projectile_flare");
    if (IsValidEdict(iEntity5)) 
    {
        DispatchKeyValue(iEntity5, "model", "models/weapons/w_models/w_flaregun_shell.mdl");
        ScaleVector(fVelocity, 0.6);
        fOrigin[0] -= 40.0;
        fOrigin[1] += 15.0;
        fOrigin[2] -= 20.0;
        fRotation[0] -= 135.0;
        fRotation[1] += 45.0;
        SetEntPropVector(iEntity5, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity5, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 1.5);
        SetEntPropVector(iEntity5, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity5, Prop_Send, "m_flDamage", fDamageFlare);
        SetEntProp(iEntity5, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntPropFloat(iEntity5, Prop_Send, "m_flModelWidthScale",0.5);
        DispatchSpawn(iEntity5);
        TeleportEntity(iEntity5, fOrigin, fRotation, fVelocity);
    }
}