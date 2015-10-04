#define ATTRIBUTE_DEFENSE_ON_KILL         1106

Attribute_1106_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DEFENSE_ON_KILL)) return;
    if (IsValidClient(iAttacker)) return;
    if (iAttacker == iClient) return;
    
    TF2_AddCondition(iAttacker, TFCond_DefenseBuffed, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DEFENSE_ON_KILL));
    
    return;
}