#define ATTRIBUTE_UBER_IS_SPEED	1185

new g_i1185Healer[MAXPLAYERS+1] = -1;
new bool:g_b1185Uber[MAXPLAYERS+1] = false;

public Action:Attribute_1185_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding) {
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    new iHealer = g_i1185Healer[iAttacker];
    if (!IsValidClient(iHealer)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;

    //Check if custom uber target, healer has attribute, client is actual heal target, healer has deployed, client Kritzed, and damage > 0
    if ((g_b1185Uber[iAttacker]) &&
        (ClientHasAttribute(iHealer, _, ATTRIBUTE_UBER_IS_SPEED)) &&
        (iAttacker == GetHealTarget(iHealer)) &&
        (IsUberchargeDeployed(iHealer)) &&
        (TF2_IsPlayerInCondition(iAttacker, TFCond_Kritzkrieged)) &&
        (fDamage > 0.0)) {

	iDamageType = RemoveCritDamageType(iDamageType);
	fDamage /= 2.22;
        return Plugin_Changed;
    }
    return Plugin_Continue;
}

//Requires that player Ubercharge is Kritzkrieg (Attribute #18)
Attribute_1185_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_UBER_IS_SPEED)) {
        new iTarget = GetHealTarget(iClient);
        if (!IsValidClient(iTarget)) return iButtons;
        g_i1185Healer[iTarget] = iClient;
        if (TF2_IsPlayerInCondition(iClient, TFCond_Kritzkrieged)) {
            TF2_AddCondition(iClient, TFCond_SpeedBuffAlly, 0.5);
        }
    }
    //For Patient, which can be another Medic as well
    new iHealer = g_i1185Healer[iClient];
    if(IsValidClient(iHealer)) {
        //Check healer for attribute, client is actual heal target, healer has deployed, and client Kritzed
        if(ClientHasAttribute(iHealer, _, ATTRIBUTE_UBER_IS_SPEED) &&
            (iClient == GetHealTarget(iHealer)) &&
            (IsUberchargeDeployed(iHealer)) &&
            (TF2_IsPlayerInCondition(iClient, TFCond_Kritzkrieged))) {

            //Set client eligible to receive effects of uber
            g_b1185Uber[iClient] = true;
            TF2_AddCondition(iClient, TFCond_SpeedBuffAlly, 0.5);
        } else {
            g_b1185Uber[iClient] = false;
        }
    }
    return iButtons;
}
//GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST GOTTA GO FAST