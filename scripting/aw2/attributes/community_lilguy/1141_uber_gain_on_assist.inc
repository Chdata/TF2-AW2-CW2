#define ATTRIBUTE_UBER_GAIN_ON_ASSIST	1141

Attribute_1141_OnDeath(iClient, &iAttacker, &iAssister, iSlot) 
{
    if (!IsValidClient(iAssister)) return;
    iSlot = GetClientSlot(iAssister);
    if (!ClientHasAttribute(iAssister, iSlot, ATTRIBUTE_UBER_GAIN_ON_ASSIST)) return;
    if (iClient == iAssister) return;
    if (IsEntityBuilding(iClient)) return;
    if (!IsPlayerAlive(iAssister)) return;
    
    //Implied for a Medigun
    new Float:fAmount = GetClientAttribute(iAssister, iSlot, ATTRIBUTE_UBER_GAIN_ON_ASSIST);
    PrintToChat(iAssister, "Assist! +%f Uber!", fAmount);
    new Float:fUber = TF2_GetPlayerUberLevel(iAssister);
    fUber += 100.0 * GetClientAttribute(iAssister, iSlot, ATTRIBUTE_UBER_GAIN_ON_ASSIST);
    TF2_SetPlayerUberLevel(iAssister, fUber);

    return;
}

