#define ATTRIBUTE_METAL_ON_KILL         1097

Attribute_1097_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_METAL_ON_KILL)) return;
    if (!IsValidClient(iAttacker)) return;
    if (iAttacker == iClient) return;
    
    new iAmount = RoundFloat(GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_METAL_ON_KILL));
    GiveEngineerMetal(iAttacker, iAmount);
    
    return;
}
