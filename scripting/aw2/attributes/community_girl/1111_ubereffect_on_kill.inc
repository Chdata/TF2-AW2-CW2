#define ATTRIBUTE_UBERDURATION_ON_KILL         1111

Attribute_1111_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_UBERDURATION_ON_KILL)) return;
    if (IsValidClient(iAttacker)) return;
    if (IsValidClient(iClient)) return;
    
    new Float:fDuration = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_UBERDURATION_ON_KILL);
    TF2_AddCondition(iAttacker, TFCond_Ubercharged, fDuration);
    
    return;
}