#define ATTRIBUTE_GIVE_METAL_ON_HIT         1076

public Action:Attribute_1076_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_GIVE_METAL_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fMetal = GetClientMaxMetal(iAttacker) * GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_GIVE_METAL_ON_HIT);
    new iMetal = RoundFloat(fMetal);
    
    GiveEngineerMetal(iAttacker, iMetal);
   
    SlagInv_AddAchievementProgress(iAttacker, "aw2_hoarder", iMetal);

    return Plugin_Continue;
}
