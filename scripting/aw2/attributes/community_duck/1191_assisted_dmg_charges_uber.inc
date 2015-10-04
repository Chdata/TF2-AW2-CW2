#define ATTRIBUTE_ASSISTED_DMG_CHARGES_UBER    1191

new g_i1191Healer[MAXPLAYERS+1] = -1;

//Adds uber on hit while healing a patient. Amount is = Damage dealt * attribute value
public Action:Attribute_1191_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding) {
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;

    new iHealer = g_i1191Healer[iAttacker];
    if (!IsValidClient(iHealer)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (!ClientHasAttribute(iHealer, iSlot, ATTRIBUTE_ASSISTED_DMG_CHARGES_UBER)) return Plugin_Continue;
    if (iAttacker == GetHealTarget(iHealer))
        {
        //Add uber to medic.
        new Float:fUber = TF2_GetPlayerUberLevel(iHealer);
        fUber += fDamage * GetClientAttribute(iHealer, iSlot, ATTRIBUTE_ASSISTED_DMG_CHARGES_UBER);
        TF2_SetPlayerUberLevel(iHealer, fUber);
        }

    return Plugin_Continue;
}