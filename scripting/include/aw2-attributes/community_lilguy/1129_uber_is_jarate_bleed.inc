#define ATTRIBUTE_UBER_IS_JARATE_BLEED    1129

new g_i1129Healer[MAXPLAYERS+1] = -1;
new bool:g_b1129Uber[MAXPLAYERS+1] = false;
new g_iParticleCount1129[MAXPLAYERS+1] = 0;

//Requires that player Ubercharge is Kritzkrieg (Attribute #18)
public Action:Attribute_1129_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding) {
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    new iHealer = g_i1129Healer[iAttacker];
    if (!IsValidClient(iHealer)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;

    //Check if custom uber target, healer has attribute, client is actual heal target, healer has deployed, client Kritzed, and damage > 0
    if ((g_b1129Uber[iAttacker]) &&
        (ClientHasAttribute(iHealer, _, ATTRIBUTE_UBER_IS_JARATE_BLEED)) &&
        (iAttacker == GetHealTarget(iHealer)) &&
        (IsUberchargeDeployed(iHealer)) &&
        (TF2_IsPlayerInCondition(iAttacker, TFCond_Kritzkrieged)) &&
        (fDamage > 0.0)) {

        iDamageType = RemoveCritDamageType(iDamageType);
	fDamage /= 2.22;
        //Apply conditions to victim for given time
        new Float:fDuration = GetClientAttribute(iHealer, _, ATTRIBUTE_UBER_IS_JARATE_BLEED);
        TF2_AddCondition(iVictim, TFCond_Jarated, fDuration);
	TF2_MakeBleed(iVictim, iAttacker, fDuration);
	return Plugin_Changed;
    }
    return Plugin_Continue;
}

Attribute_1129_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
    //For Medic with attribute
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_UBER_IS_JARATE_BLEED)) {
        //Dont need to remove Kritz from a Medic that has it deployed
        new iTarget = GetHealTarget(iClient);
        if (!IsValidClient(iTarget)) return iButtons;
        g_i1129Healer[iTarget] = iClient;
    }

    //For Patient, which can be another Medic as well
    new iHealer = g_i1129Healer[iClient];
    if(IsValidClient(iHealer)) {
        //Check healer for attribute, client is actual heal target, healer has deployed, and client Kritzed
        if(ClientHasAttribute(iHealer, _, ATTRIBUTE_UBER_IS_JARATE_BLEED) &&
            (iClient == GetHealTarget(iHealer)) &&
            (IsUberchargeDeployed(iHealer)) &&
            (TF2_IsPlayerInCondition(iClient, TFCond_Kritzkrieged))) {

            //Set client eligible to receive effects of uber
            g_b1129Uber[iClient] = true;
            //Set fancy particles
            g_iParticleCount1129[iClient]++;
            if (g_iParticleCount1129[iClient] >= 30) {
                new iWeap = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
                AttachParticle(iWeap, PARTICLE_SPECIALUBER, 0.5);
                g_iParticleCount1129[iClient] = 0;
            }
        } else {
            g_b1129Uber[iClient] = false;
        }
    }

    return iButtons;
}
