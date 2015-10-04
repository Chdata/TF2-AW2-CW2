#define ATTRIBUTE_DOVE_RAIN_FIXED		  1162

Attribute_1162_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DOVE_RAIN_FIXED)) return;
    if (!IsValidEdict(iEntity)) return;
    
    EntIndexToEntRef(iEntity);
    CreateTimer(0.15, Dove_Rain_Fixed, iEntity);
}

public Action:Dove_Rain_Fixed(Handle:hTimer, any:iEntRef) 
{
    new iEntity = EntRefToEntIndex(iEntRef);
    if (!IsValidEdict(iEntity)) return;
       
    AttachProjectileModel(iEntity, PROJECTILE_MODEL_8, "fly_cycle");
    new iOwner = GetEntProp(iEntity, Prop_Send, "m_hOwnerEntity");
    new Float:fTime1162 = GetClientAttribute(iOwner, _, ATTRIBUTE_DOVE_RAIN_FIXED);
    CreateTimer(fTime1162, Dove_Rain_Fixed, iEntity);
    fTime1162 *= 1.33;
    CreateTimer(fTime1162, Dove_Rain_Bombard, iEntity);
    fTime1162 *= 1.33;
    CreateTimer(fTime1162, Dove_Rain_Bombard, iEntity);
    fTime1162 *= 1.33;
    CreateTimer(fTime1162, Dove_Rain_Bombard, iEntity);
    EntIndexToEntRef(iEntity);
}

public Action:Dove_Rain_Bombard(Handle:hTimer, any:iEntRef) 
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
    
    new iEntity2 = CreateEntityByName("tf_projectile_jar_milk");
    if (IsValidEdict(iEntity2)) 
    {
        ScaleVector(fVelocity, 0.5);
        SetEntProp(iEntity2, Prop_Send, "m_hOwnerEntity", iOwner);
        DispatchSpawn(iEntity2);
        TeleportEntity(iEntity2, fOrigin, fRotation, fVelocity);
    }
}