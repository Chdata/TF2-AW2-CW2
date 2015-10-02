#define ATTRIBUTE_SPEED_ON_MAJOR_HIT         1113

Attribute_1113_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SPEED_ON_MAJOR_HIT)) return;

    new weaponentity = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
    AttachParticle(weaponentity, PARTICLE_BLUR, -1.0);
}

public Action:Attribute_1113_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_SPEED_ON_MAJOR_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    TF2_AddCondition(iAttacker, TFCond_SpeedBuffAlly, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_SPEED_ON_MAJOR_HIT));
    
    return Plugin_Continue;
}
//Directly linked to script in advancedweaponiser2.sp
public Action:ClientSwitchWeapon_Attribute1113(iClient, iEntity)
{
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_SPEED_ON_MAJOR_HIT)) return;
    if (!IsValidClient(iClient)) return;
    
    new iSlot = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SPEED_ON_MAJOR_HIT)) {
    AttachParticle(iSlot, PARTICLE_BLUR, -1.0);
    }
    
    return;
}