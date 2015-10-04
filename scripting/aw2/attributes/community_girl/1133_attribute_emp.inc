#define ATTRIBUTE_EMP_STICKY      1133

new Float:StunTime1133[MAX_EDICTS+1] = 0.0;
new Float:ExecutedStun1133[MAX_EDICTS+1] = 0.0;

Attribute_1133_ProjCreated(iEntity, iClient, iSlot)
{
    if (!IsValidEdict(iEntity)) return;
    if (!IsValidClient(iClient)) return;
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_EMP_STICKY))
	{        
        new Float:fVelocity[3];
        new Float:f_StickyDamage = GetRandomFloat(15.0,60.0);
        GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
        ScaleVector(fVelocity, 1.45);
        SetEntityModel(iEntity, PROJECTILE_MODEL_24);
        SetEntPropVector(iEntity, Prop_Send, "m_vecVelocity", fVelocity);
        GetEntPropVector(iEntity, Prop_Data, "m_vInitialVelocity", fVelocity);
        ScaleVector(fVelocity, 1.45);
        SetEntPropVector(iEntity, Prop_Send, "m_vInitialVelocity", fVelocity);
        SetEntPropFloat(iEntity, Prop_Send, "m_flDamage", f_StickyDamage);
        SetEntPropFloat(iEntity, Prop_Send, "m_DmgRadius", 72.0);
        SetEntPropFloat(iEntity, Prop_Send, "m_flModelWidthScale",0.94);
    }
}

public Action:Attribute_1133_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_EMP_STICKY)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;

    if (!bBuilding)
    {
        new iEntity = iVictim;
        if (!IsValidEdict(iEntity)) return Plugin_Continue;
        if (IsClassname(iEntity, "obj_sentrygun"))
        {
        CreateTimer(0.1, Execute_Stun, iEntity);
        StunTime1133[iEntity] += 0.5;
        }
        fDamage *= 1.5;
    }
    
    return Plugin_Changed;
}
    
public Action:Execute_Stun(Handle:hTimer, any:iEntity) {
    if (!IsValidEdict(iEntity)) return;
    
    if (ExecutedStun1133[iEntity] == 0.0) {
    SetEntProp(iEntity, Prop_Send, "m_bDisabled", 1);
    StunTime1133[iEntity] = ExecutedStun1133[iEntity];
    StunTime1133[iEntity] = 0.0;
    CreateTimer(ExecutedStun1133[iEntity], Expire_Stun, iEntity);
    }
}

public Action:Expire_Stun(Handle:hTimer, any:iEntity) {
    if (!IsValidEdict(iEntity)) return;
    
    SetEntProp(iEntity, Prop_Send, "m_bDisabled", 0);
    ExecutedStun1133[iEntity] = 0.0;
}