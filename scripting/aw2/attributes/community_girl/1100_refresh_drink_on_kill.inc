#define ATTRIBUTE_REFRESH_DRINK_ON_KILL            1100

Attribute_1100_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_REFRESH_DRINK_ON_KILL)) return;
    if (IsValidClient(iAttacker)) return;
    if (IsValidClient(iClient)) return;
    
    new Float:fDrinkMeter = GetEntPropFloat(iAttacker, Prop_Send, "m_flEnergyDrinkMeter");
    fDrinkMeter = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_REFRESH_DRINK_ON_KILL);
    SetEntPropFloat(iAttacker, Prop_Send, "m_flEnergyDrinkMeter", fDrinkMeter);
    
    return;
}