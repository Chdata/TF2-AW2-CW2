#define ATTRIBUTE_ARROW_RAIN		  1119

Attribute_1119_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ARROW_RAIN)) return;
    if (!IsValidEdict(iEntity)) return;
    
    EntIndexToEntRef(iEntity);
    new Float:fTime1119 = GetClientAttribute(iClient, iSlot, ATTRIBUTE_ARROW_RAIN);
    CreateTimer(fTime1119, Arrow_Rain, iEntity);
}

public Action:Arrow_Rain(Handle:hTimer, any:iEntRef) 
{
    new iEntity = EntRefToEntIndex(iEntRef);
    if (!IsValidEdict(iEntity)) return;

    new Float:fOrigin[3];
    new Float:fVelocity[3];
    new Float:fRotation[3];
    GetEntPropVector(iEntity, Prop_Data, "m_vecOrigin", fOrigin);
    GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
    GetEntPropVector(iEntity, Prop_Data, "m_angRotation", fRotation);

    new iSkin = GetEntProp(iEntity, Prop_Send, "m_nSkin");
    new iCritical = GetEntProp(iEntity, Prop_Send, "m_bCritical");
    new iOwner = GetEntProp(iEntity, Prop_Send, "m_hOwnerEntity");
    new Float:fDamageArrow = GetEntPropFloat(iEntity, Prop_Send, "m_flDamage");
    fDamageArrow *= 0.5;
    
    new iEntity2 = CreateEntityByName("tf_projectile_arrow");
    if (IsValidEdict(iEntity2)) 
    {
        DispatchKeyValue(iEntity2, "model", "models/weapons/w_models/w_arrow.mdl");
        ScaleVector(fVelocity, 0.5);
        fOrigin[0] += 25.0;
        fOrigin[1] += 20.0;
        fOrigin[2] -= 15.0;
        SetEntPropVector(iEntity2, Prop_Send, "m_vecVelocity", fVelocity);

        GetEntPropVector(iEntity2, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 0.5);
        SetEntPropVector(iEntity2, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity2, Prop_Send, "m_flDamage", fDamageArrow);
        SetEntProp(iEntity2, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntProp(iEntity2, Prop_Send, "m_nSkin", iSkin);
        SetEntProp(iEntity2, Prop_Send, "m_bCritical", iCritical);
        DispatchSpawn(iEntity2);
        TeleportEntity(iEntity2, fOrigin, fRotation, fVelocity);
    }
    new iEntity3 = CreateEntityByName("tf_projectile_arrow");
    if (IsValidEdict(iEntity3)) 
    {
        DispatchKeyValue(iEntity3, "model", "models/weapons/w_models/w_arrow.mdl");
        ScaleVector(fVelocity, 0.55);
        fOrigin[0] -= 50.0;
        fOrigin[1] -= 40.0;
        fOrigin[2] += 30.0;
        SetEntPropVector(iEntity3, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity3, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 0.5);
        SetEntPropVector(iEntity3, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity3, Prop_Send, "m_flDamage", fDamageArrow);
        SetEntProp(iEntity3, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntProp(iEntity3, Prop_Send, "m_nSkin", iSkin);
        SetEntProp(iEntity3, Prop_Send, "m_bCritical", iCritical);
        DispatchSpawn(iEntity3);
        TeleportEntity(iEntity3, fOrigin, fRotation, fVelocity);
    }
    new iEntity4 = CreateEntityByName("tf_projectile_arrow");
    if (IsValidEdict(iEntity4)) 
    {
        DispatchKeyValue(iEntity4, "model", "models/weapons/w_models/w_arrow.mdl");
        ScaleVector(fVelocity, 0.45);
        fOrigin[0] += 25.0;
        fOrigin[1] -= 20.0;
        fOrigin[2] += 15.0;
        SetEntPropVector(iEntity4, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity4, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 0.5);
        SetEntPropVector(iEntity4, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity4, Prop_Send, "m_flDamage", fDamageArrow);
        SetEntProp(iEntity4, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntProp(iEntity4, Prop_Send, "m_nSkin", iSkin);
        SetEntProp(iEntity4, Prop_Send, "m_bCritical", iCritical);
        DispatchSpawn(iEntity4);
        TeleportEntity(iEntity4, fOrigin, fRotation, fVelocity);
    }
    new iEntity5 = CreateEntityByName("tf_projectile_arrow");
    if (IsValidEdict(iEntity5)) 
    {
        DispatchKeyValue(iEntity5, "model", "models/weapons/w_models/w_arrow.mdl");
        ScaleVector(fVelocity, 0.6);
        fOrigin[0] -= 40.0;
        fOrigin[1] += 15.0;
        fOrigin[2] -= 20.0;
        SetEntPropVector(iEntity5, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity5, Prop_Send, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 0.5);
        SetEntPropVector(iEntity5, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity5, Prop_Send, "m_flDamage", fDamageArrow);
        SetEntProp(iEntity5, Prop_Send, "m_hOwnerEntity", iOwner);
        SetEntProp(iEntity5, Prop_Send, "m_nSkin", iSkin);
        SetEntProp(iEntity5, Prop_Send, "m_bCritical", iCritical);
        DispatchSpawn(iEntity5);
        TeleportEntity(iEntity5, fOrigin, fRotation, fVelocity);
    }
}