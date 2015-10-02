#define ATTRIBUTE_DMG_EQUALS_ENEMY_HEALTH      1169

// girl is Slag Gaming.

public Action:Attribute_1169_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DMG_EQUALS_ENEMY_HEALTH)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    //Prevention of 3x of the damage actually wanted
    if (IsDamageTypeCrit(iDamageType)) {
	    iDamageType = RemoveCritDamageType(iDamageType);
    }

    new iHealth = GetClientHealth(iVictim);
    new Float:fRatio = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DMG_EQUALS_ENEMY_HEALTH);
    fDamage = iHealth*fRatio;
    //girl added a pretty particle
    AttachParticle(iVictim, PARTICLE_IMPACT_BLUE, 1.4);
    
    return Plugin_Changed;
}
