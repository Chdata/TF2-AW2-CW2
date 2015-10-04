#define ATTRIBUTE_MILK_ON_HIT            1123

Attribute_1123_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SPEED_ON_MAJOR_HIT)) return;

    new weaponentity = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
    AttachParticle(weaponentity, PARTICLE_ZEUS_CRACKLE, -1.0);
}

public Action:Attribute_1123_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_MILK_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 10.0) return Plugin_Continue;
    
    TF2_AddCondition(iVictim, TFCond_Milked, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_MILK_ON_HIT));
    
    return Plugin_Continue;
}