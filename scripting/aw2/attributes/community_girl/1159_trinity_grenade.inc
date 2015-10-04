#define ATTRIBUTE_TRINITY_GRENADE      1159

new g_i1159GrenadeCount[MAXPLAYERS+1] = 0;
new g_i1159GrenadeType[MAX_EDICTS+1] = 0;

Attribute_1159_ProjCreated(iEntity, iClient, iSlot)
{
    if (!IsValidEdict(iEntity)) return;
    if (!IsValidClient(iClient)) return;
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_TRINITY_GRENADE))
	{
        if (g_i1159GrenadeCount[iClient] < 3) {
        g_i1159GrenadeCount[iClient]++;
        }
        if (g_i1159GrenadeCount[iClient] >= 3) {
        g_i1159GrenadeCount[iClient] = 0;
        }
        
        new Float:fVelocity[3];
        if (g_i1159GrenadeCount[iClient] == 0) {
        GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
        ScaleVector(fVelocity, 0.65);
        SetEntityModel(iEntity, PROJECTILE_MODEL_21);
        SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity, Prop_Data, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 0.65);
        SetEntPropVector(iEntity, Prop_Data, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity, Prop_Send, "m_DmgRadius", 144.0);
        SetEntPropFloat(iEntity, Prop_Send, "m_flModelWidthScale",1.01);
        g_i1159GrenadeType[iEntity] = 1;
        }
        if (g_i1159GrenadeCount[iClient] == 1) {
        SetEntityModel(iEntity, PROJECTILE_MODEL_9);
        GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
        ScaleVector(fVelocity, 0.50);
        SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity, Prop_Data, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 0.50);
        SetEntPropVector(iEntity, Prop_Data, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity, Prop_Send, "m_DmgRadius", 72.0);
        SetEntPropFloat(iEntity, Prop_Send, "m_flModelWidthScale",1.02);
        g_i1159GrenadeType[iEntity] = 2;
        }
        if (g_i1159GrenadeCount[iClient] == 2) {
        SetEntityModel(iEntity, PROJECTILE_MODEL_23);
        GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
        ScaleVector(fVelocity, 1.50);
        SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity, Prop_Data, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 1.50);
        SetEntPropVector(iEntity, Prop_Data, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity, Prop_Send, "m_DmgRadius", 216.0);
        SetEntPropFloat(iEntity, Prop_Send, "m_flModelWidthScale",1.03);
        g_i1159GrenadeType[iEntity] = 3;
        }
    }
}

public Action:Attribute_1159_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_TRINITY_GRENADE)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new iEntity;
    iEntity = -1;
    while ((iEntity = FindEntityByClassname2(iEntity, "tf_projectile_pipe")) != -1) 
    {
        if (IsValidEdict(iEntity)) 
        {    
        if (g_i1159GrenadeType[iEntity] == 1)
        {
                new iGrenadeHeal = GetRandomInt(35,50);
                new iHealth = GetClientHealth(iAttacker);
                iHealth += iGrenadeHeal;
                new iOverHeal = GetClientMaxOverHeal(iAttacker);
                if (iHealth > iOverHeal) iHealth = iOverHeal;
                SetEntityHealth(iAttacker, iHealth);
                fDamage *= 0.80;
        }
        else if (g_i1159GrenadeType[iEntity] == 2)
        {
            NormalizeVector(fForce, fForce);
            if (fForce[2] < 0.2) fForce[2] = 0.2;
            
            new Float:fScale = 1250.0;
            ScaleVector(fForce, fScale);
            if (fForce[2] < 320.0 && fDamage >= 0.0) fForce[2] = 320.0;
            
            decl Float:vClientVelocity[3];
            GetVelocity(iVictim, vClientVelocity);
            AddVectors(vClientVelocity, fForce, vClientVelocity);
            TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vClientVelocity);
            fDamage *= 0.90;
            
        }
        else if (g_i1159GrenadeType[iEntity] == 3)
        {
            if (bBuilding) 
            {
            fDamage *= 1.60;
            }
            fDamage *= 0.75;
        }
        }
    }
    
    return Plugin_Changed;
}