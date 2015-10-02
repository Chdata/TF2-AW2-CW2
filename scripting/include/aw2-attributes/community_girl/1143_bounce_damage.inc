#define ATTRIBUTE_BOUNCE_DAMAGE      1143

public Action:Attribute_1143_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_BOUNCE_DAMAGE)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_PROJECTILES_BOUNCE)) return Plugin_Continue;
    
    new iEntity;
    iEntity = -1;
    new iOwner;
    while ((iEntity = FindEntityByClassname2(iEntity, "tf_projectile_arrow")) != -1) {
    if (IsValidEdict(iEntity)) {
    iOwner = GetEntPropEnt(iEntity, Prop_Send, "m_hOwnerEntity");
    if (!ClientHasAttribute(iOwner, iSlot, ATTRIBUTE_BOUNCE_DAMAGE)) return Plugin_Continue;
    AttachParticle(iEntity, PARTICLE_BLUR, 10.0);
    if (g_iProjectileBounces[iEntity] == 0)
    {
    fDamage *= 1.0;
    }
    else if (g_iProjectileBounces[iEntity] == 1)
    {
    fDamage *= 1.20;
    }
    else if (g_iProjectileBounces[iEntity] == 2)
    {
    fDamage *= 1.40;
    }
    else if (g_iProjectileBounces[iEntity] == 3)
    {
    fDamage *= 1.05;
    }
    else if (g_iProjectileBounces[iEntity] == 4)
    {
    fDamage *= 0.70;
    }
    else if (g_iProjectileBounces[iEntity] == 5)
    {
    fDamage *= 0.35;
    }
    else if (g_iProjectileBounces[iEntity] >= 6)
    {
    fDamage *=0.05;
    }
    }
    }
    
    return Plugin_Changed;
}