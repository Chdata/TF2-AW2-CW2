#define ATTRIBUTE_COLA_ON_KILL         1107

Attribute_1107_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_COLA_ON_KILL)) return;
    if (IsValidClient(iAttacker)) return;
    if (IsValidClient(iClient)) return;
    
    TF2_AddCondition(iAttacker, TFCond_CritCola, 5.0);
    
    return;
}