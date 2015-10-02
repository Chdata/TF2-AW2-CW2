#define ATTRIBUTE_IMBUE_FLARES_ALT_FIRE        1153

new g_iProjectileEffect1153[MAX_EDICTS+1] = 0;
new bool:g_bAltFired1153[MAXPLAYERS+1] = false;

Attribute_1153_ProjCreated(iEntity, iClient, iSlot)
{
    g_iProjectileEffect1153[iEntity] = 0;
    if (g_bAltFired1153[iClient])
    {
        new Float:fCheck_Proj = GetClientAttribute(iClient, iSlot, ATTRIBUTE_IMBUE_FLARES_ALT_FIRE);
        if (fCheck_Proj == 0.0)
        {
        g_iProjectileEffect1153[iEntity] = 0;
        }
        else if (fCheck_Proj == 1.0)
        {
        g_iProjectileEffect1153[iEntity] = 1;
        decl Float:vFlareVelocity[3];
        decl Float:vDifference[3];
        GetEntPropVector(iEntity, Prop_Data, "m_vecAbsVelocity", vFlareVelocity);
        decl Float:vTargetOrigin[3];
        GetClientPointPosition(iClient, vTargetOrigin, MASK_VISIBLE);
        decl Float:vFlareOrigin[3];
        GetEntPropVector(iEntity, Prop_Data, "m_vecAbsOrigin", vFlareOrigin);
        new Float:fFlareSpeed = GetVectorLength(vFlareVelocity)-700.0;
        SetEntPropFloat(iEntity, Prop_Send, "m_flModelWidthScale",2.01);
        SubtractVectors(vTargetOrigin, vFlareOrigin, vDifference);
        ScaleVector(vDifference, fFlareSpeed);
        SetEntPropVector(iEntity, Prop_Data, "m_vecAbsVelocity", vDifference);
        }
        else if (fCheck_Proj == 2.0)
        {
        g_iProjectileEffect1153[iEntity] = 2;
        }
        else if (fCheck_Proj == 3.0)
        {        
        new Float:fOrigin[3];
        new Float:fVelocity[3];
        new Float:fRotation[3];
        new Float:vFlareOrigin[3];
        GetEntPropVector(iEntity, Prop_Data, "m_vecOrigin", fOrigin);
        GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity, Prop_Data, "m_angRotation", fRotation);
        GetEntPropVector(iEntity, Prop_Data, "m_vecAbsOrigin", vFlareOrigin);
        
        new iEntity2 = CreateEntityByName("tf_projectile_flare");
        if (IsValidEdict(iEntity2)) 
        {
        fOrigin[0] += 5.0;
        fOrigin[1] += 2.5;
        fOrigin[2] += 1.0;
        DispatchKeyValue(iEntity2, "model", "models/weapons/w_models/w_flaregun_shell.mdl");
        SetEntPropVector(iEntity2, Prop_Send, "m_vecVelocity", fVelocity);
        SetEntPropVector(iEntity2, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntProp(iEntity2, Prop_Send, "m_hOwnerEntity", GetEntProp(iEntity, Prop_Send, "m_hOwnerEntity"));
        DispatchSpawn(iEntity2);
        SetEntPropFloat(iEntity2, Prop_Send, "m_flModelWidthScale",0.85);
        TeleportEntity(iEntity2, fOrigin, fRotation, fVelocity);
        
        new iEntity3 = CreateEntityByName("tf_projectile_flare");
        fOrigin[0] -= 10.0;
        fOrigin[1] -= 5;
        fOrigin[2] -= 2.0;
        DispatchKeyValue(iEntity3, "model", "models/weapons/w_models/w_flaregun_shell.mdl");
        SetEntPropVector(iEntity3, Prop_Send, "m_vecVelocity", fVelocity);
        SetEntPropVector(iEntity3, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntProp(iEntity3, Prop_Send, "m_hOwnerEntity", GetEntProp(iEntity, Prop_Send, "m_hOwnerEntity"));
        DispatchSpawn(iEntity3);
        SetEntPropFloat(iEntity3, Prop_Send, "m_flModelWidthScale",0.85);
        TeleportEntity(iEntity3, fOrigin, fRotation, fVelocity);

        g_iProjectileEffect1153[iEntity] = 3;
        g_iProjectileEffect1153[iEntity2] = 3;
        g_iProjectileEffect1153[iEntity3] = 3;
    }
}
        }
}

Attribute_1153_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_IMBUE_FLARES_ALT_FIRE))
	{
        g_bAltFired1153[iClient] = false;
        
        if (iButtons & IN_ATTACK2 == IN_ATTACK2)
		{
            g_bAltFired1153[iClient] = true;
            iButtons |= IN_ATTACK;
		}
	}
	return iButtons;
}


public Action:Attribute_1153_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_IMBUE_FLARES_ALT_FIRE)) return Plugin_Continue;
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!g_bAltFired1153[iAttacker]) return Plugin_Continue;
        
    new iEntity;
    iEntity = -1;
    new iOwner;
    while ((iEntity = FindEntityByClassname2(iEntity, "tf_projectile_arrow")) != -1) {
    if (IsValidEdict(iEntity)) {
    iOwner = GetEntPropEnt(iEntity, Prop_Send, "m_hOwnerEntity");
    if (!IsValidClient(iOwner)) return Plugin_Continue;
    
    if (g_iProjectileEffect1153[iEntity] <= 1)
    {
    fDamage *= 0.50;
    NormalizeVector(fForce, fForce);
    if (fForce[2] < 0.2) fForce[2] = 0.2;
    
    new Float:fScale1153 = fDamage*7.5;
    if (fScale1153 < 100.0) fScale1153 = 100.0;
    if (fScale1153 > 1100.0) fScale1153 = 1100.0;
    ScaleVector(fForce, fScale1153);
    if (fForce[2] < 320.0 && fDamage >= 10.0) fForce[2] = 320.0;
    
    decl Float:vClientVelocity[3];
    GetVelocity(iVictim, vClientVelocity);
    AddVectors(vClientVelocity, fForce, vClientVelocity);
    TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vClientVelocity);
    }
    else if (g_iProjectileEffect1153[iEntity] == 2.0)
    {
        TF2_AddCondition(iVictim, TFCond_OnFire, 5.0);
        fDamage *= 0.25;
    }
    else if (g_iProjectileEffect1153[iEntity] == 3.0)
    {
        fDamage *= 1.15;
    }
}
}
    
    return Plugin_Changed;
}