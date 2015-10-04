#define ATTRIBUTE_ASSISTED_DMG_BONUS   1192

new g_i1192Healer[MAXPLAYERS+1] = -1;

//Damage bonus for patient
public Action:Attribute_1192_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding) {
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;

    new iHealer = g_i1192Healer[iAttacker];
    if (!IsValidClient(iHealer)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (!ClientHasAttribute(iHealer, iSlot, ATTRIBUTE_ASSISTED_DMG_BONUS)) return Plugin_Continue;
    if (iAttacker == GetHealTarget(iHealer))
    fDamage = fDamage * GetClientAttribute(iHealer, iSlot, ATTRIBUTE_ASSISTED_DMG_BONUS);

    return Plugin_Changed;
}