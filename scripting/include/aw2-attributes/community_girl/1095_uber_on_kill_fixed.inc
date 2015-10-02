#define ATTRIBUTE_UBER_ON_KILL         1095

Attribute_1095_OnDeath(iClient, &iAttacker, &iAssister, iSlot) 
{
    if (!IsValidClient(iAttacker)) return;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_UBER_ON_KILL)) return;
    if (iClient == iAttacker) return;
    if (IsEntityBuilding(iClient)) return;
    if (!IsPlayerAlive(iAttacker)) return;
    
    new Float:fUber1095 = TF2_GetPlayerUberLevel(iAttacker);
    fUber1095 += 100.0*GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_UBER_ON_KILL);
    TF2_SetPlayerUberLevel(iAttacker, fUber1095);

    return;
}
