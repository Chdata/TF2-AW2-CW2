#define ATTRIBUTE_DEMOCHARGE_ON_HIT            1099

public Action:Attribute_1099_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DEMOCHARGE_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:m_flChargeMeter = GetEntPropFloat(iAttacker, Prop_Send, "m_flChargeMeter");
    m_flChargeMeter += GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DEMOCHARGE_ON_HIT);
    
    if (m_flChargeMeter >= 100.0)
    {
    SetEntPropFloat(iAttacker, Prop_Send, "m_flChargeMeter", 100.0);
    }
    
    if (m_flChargeMeter < 100.0)
    {
    SetEntPropFloat(iAttacker, Prop_Send, "m_flChargeMeter", m_flChargeMeter);
    }
    
    return Plugin_Continue;
}