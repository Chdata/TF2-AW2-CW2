#define ATTRIBUTE_DISABLE_ENEMY_WEAPON_SILENT       1069

public Action:Attribute_1069_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DISABLE_ENEMY_WEAPON_SILENT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fTime = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DISABLE_ENEMY_WEAPON_SILENT);
       
    MakeSlotSleep(iVictim, 0, fTime, false);
    MakeSlotSleep(iVictim, 1, fTime, false);
    
    return Plugin_Continue;
}