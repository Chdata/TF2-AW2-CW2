#define ATTRIBUTE_ON_HIT_MARK4DEATH_MELEEONLY         1165

public Action:Attribute_1165_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_ON_HIT_MARK4DEATH_MELEEONLY)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;

    new Float:fDuration1165 = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_ON_HIT_MARK4DEATH_MELEEONLY);
    
    TF2_AddCondition(iAttacker, TFCond_RestrictToMelee, fDuration1165);
    TF2_AddCondition(iAttacker, TFCond_MarkedForDeath, fDuration1165);
    //girl added pretty particles
    //I hope this will look pretty, if not, find a better particle effect
    AttachParticle(iVictim, PARTICLE_EXPLOSION_FLASH, 1.2);
    AttachParticle(iAttacker, PARTICLE_EXPLOSION_FLASH, 1.2);

    return Plugin_Continue;
}