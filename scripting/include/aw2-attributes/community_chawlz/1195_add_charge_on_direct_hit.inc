#define ATTRIBUTE_ADD_CHARGE_ON_HIT        1195

public Action:Attribute_1195_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_ADD_CHARGE_ON_HIT)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;

    new Float:fDamageThreshold = 80.0;
    new Float:fThresholdMulti = 1.0;

    if (ClientHasAttribute(iVictim, _, 64)) {fThresholdMulti = GetClientAttribute(iVictim, _, 64);}
    if (ClientHasAttribute(iVictim, _, 65)) {fThresholdMulti = GetClientAttribute(iVictim, _, 65);}
    if (TF2_IsPlayerInCondition(iVictim, TFCond_DefenseBuffed)) {fThresholdMulti += 0.35;}
    if (IsDamageTypeCrit(iDamageType)) {fThresholdMulti *= 3;}
    fDamageThreshold *= fThresholdMulti;
    if (fDamage <= fDamageThreshold) return Plugin_Continue;
    
    new Float:fCharge = GetEntPropFloat(iAttacker, Prop_Send, "m_flChargeMeter");
    new Float:fChargeMultiplier = GetClientAttribute(iAttacker, _, ATTRIBUTE_ADD_CHARGE_ON_HIT) * 100.0;

    fCharge += fChargeMultiplier;

    if (fCharge >= 100.0)
    {
    SetEntPropFloat(iAttacker, Prop_Send, "m_flChargeMeter", 100.0);
    }
    
    if (fCharge < 100.0)
    {
    SetEntPropFloat(iAttacker, Prop_Send, "m_flChargeMeter", fCharge);
    }

    
    return Plugin_Continue;
}
