#define ATTRIBUTE_UBER_IS_MINICRIT_DEF	1140

new g_i1140Healer[MAXPLAYERS+1] = -1;
new bool:g_b1140Uber[MAXPLAYERS+1] = false;

public Action:Attribute_1140_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding) {
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    new iHealer = g_i1140Healer[iAttacker];
    if (!IsValidClient(iHealer)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;

    if ((g_b1140Uber[iAttacker]) &&
        (ClientHasAttribute(iHealer, _, ATTRIBUTE_UBER_IS_MINICRIT_DEF)) &&
        (iAttacker == GetHealTarget(iHealer)) &&
        (IsUberchargeDeployed(iHealer)) &&
        (TF2_IsPlayerInCondition(iAttacker, TFCond_Kritzkrieged)) &&
        (fDamage > 0.0)) {

        //Still keeps crit look at the moment, will fix once defense buff is figured out
	iDamageType = RemoveCritDamageType(iDamageType);
	ApplyMinicrit(iVictim, iAttacker);
	fDamage /= 2.22;
        return Plugin_Changed;
    }
    return Plugin_Continue;
}

//Requires that player Ubercharge is Kritzkrieg (Attribute #18)
Attribute_1140_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_UBER_IS_MINICRIT_DEF)) {
        new iTarget = GetHealTarget(iClient);
        if (!IsValidClient(iTarget)) return iButtons;
        g_i1140Healer[iTarget] = iClient;
        if (TF2_IsPlayerInCondition(iClient, TFCond_Kritzkrieged)) {
            TF2_AddCondition(iClient, TFCond_DefenseBuffed, 0.5);
        }
    }
    //For Patient, which can be another Medic as well
    new iHealer = g_i1140Healer[iClient];
    if(IsValidClient(iHealer)) {
        //Check healer for attribute, client is actual heal target, healer has deployed, and client Kritzed
        if(ClientHasAttribute(iHealer, _, ATTRIBUTE_UBER_IS_MINICRIT_DEF) &&
            (iClient == GetHealTarget(iHealer)) &&
            (IsUberchargeDeployed(iHealer)) &&
            (TF2_IsPlayerInCondition(iClient, TFCond_Kritzkrieged))) {

            //Set client eligible to receive effects of uber
            g_b1140Uber[iClient] = true;
            TF2_AddCondition(iClient, TFCond_DefenseBuffed, 0.5);
        } else {
            g_b1140Uber[iClient] = false;
        }
    }
    return iButtons;
}
