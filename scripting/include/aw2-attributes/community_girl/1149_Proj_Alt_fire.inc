#define ATTRIBUTE_IMBUE_PROJ_ALT_FIRE        1149

new g_iProjectileEffect1149[MAX_EDICTS+1] = 0;
new bool:g_bAltFired1149[MAXPLAYERS+1] = false;

Attribute_1149_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_IMBUE_PROJ_ALT_FIRE)) return;
    if (!IsValidEdict(iEntity)) return;
    if (!g_bAltFired1149[iClient]) return;
    
    new Float:fEffect1149 = GetClientAttribute(iClient, iSlot, ATTRIBUTE_IMBUE_PROJ_ALT_FIRE);
    new Float:fVelocity[3];
    
    if (fEffect1149 == 0.0) {
    g_iProjectileEffect1149[iEntity] = 0;
    GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
    ScaleVector(fVelocity, 0.70);
    SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
    }
    if (fEffect1149 == 1.0) {
    g_iProjectileEffect1149[iEntity] = 1;
    GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
    ScaleVector(fVelocity, 1.50);
    SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
    }
    if (fEffect1149 == 2.0) {
    g_iProjectileEffect1149[iEntity] = 2;
    GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
    ScaleVector(fVelocity, 3.0);
    SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
    }
    if (fEffect1149 == 3.0) {
    g_iProjectileEffect1149[iEntity] = 3;
    }
    if (fEffect1149 == 4.0) {
    g_iProjectileEffect1149[iEntity] = 4;
    }
    if (fEffect1149 == 5.0) {
    g_iProjectileEffect1149[iEntity] = 5;
    }
    EntIndexToEntRef(iEntity);   
}

Attribute_1149_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_IMBUE_PROJ_ALT_FIRE))
	{
        g_bAltFired1149[iClient] = false;
        
        if (iButtons & IN_ATTACK2 == IN_ATTACK2)
		{
            g_bAltFired1149[iClient] = true;
            iButtons |= IN_ATTACK;
		}
	}
	return iButtons;
}

public Action:Attribute_1149_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_IMBUE_PROJ_ALT_FIRE)) return Plugin_Continue;
    
    new String:strEntities[][255] = {"tf_projectile"};
    for (new i = 0; i < sizeof(strEntities); i++)
    {
        new iIndex = -1;
        while ((iIndex = FindEntityByClassname(iIndex, strEntities[i])) != -1)
        {
            if (!IsValidEdict(iIndex)) return Plugin_Continue;
        }
    }
    new iEntRef = EntIndexToEntRef(iIndex);
    new iEntity = EntRefToEntIndex(iEntRef);
    if (!IsValidEdict(iEntity)) return Plugin_Continue;
    
    if (g_iProjectileEffect1149[iEntity] <= 0) {
    fDamage *= 1.20;
    }
    else if (g_iProjectileEffect1149[iEntity] <= 1) {
    fDamage *= 0.5;
    NormalizeVector(fForce, fForce);
    if (fForce[2] < 0.2) fForce[2] = 0.2;
    
    new Float:fScale = fDamage*5;
    if (fScale < 100.0) fScale = 100.0;
    if (fScale > 750.0) fScale = 750.0;
    ScaleVector(fForce, fScale);
    if (fForce[2] < 320.0 && fDamage >= 10.0) fForce[2] = 320.0;
    
    decl Float:vClientVelocity[3];
    GetVelocity(iVictim, vClientVelocity);
    AddVectors(vClientVelocity, fForce, vClientVelocity);
    TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vClientVelocity);
    }
    else if (g_iProjectileEffect1149[iEntity] <= 2) {
    fDamage = 0;
    }
    
    return Plugin_Changed;
}

Attribute_1149_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK)) return;
    if (!g_bAltFired1149[iClient]) return;
    
    EmitSoundToAll(SOUND_ALT_FIRE_PROJ, iClient, _, SNDLEVEL_NORMAL);
}
    //AcceptEntityInput(iEntity, "Kill" );