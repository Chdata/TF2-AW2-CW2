#define ATTRIBUTE_LOSE_CHARGE_WHEN_HIT        1183

public Action:Attribute_1183_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iVictim, 0, ATTRIBUTE_LOSE_CHARGE_WHEN_HIT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!TF2_IsPlayerInCondition(iVictim, TFCond_Zoomed)) return Plugin_Continue;
    
    new iWeapon = GetEntPropEnt(iVictim, Prop_Send, "m_hActiveWeapon");
    new Float:fCharge = GetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage");

    if (fCharge >= fDamage * GetClientAttribute(iVictim, _, ATTRIBUTE_LOSE_CHARGE_WHEN_HIT))
        {
        fCharge -= fDamage * GetClientAttribute(iVictim, _, ATTRIBUTE_LOSE_CHARGE_WHEN_HIT);
        }
    else
        {
        fCharge = 0.0;
        }
    
    SetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage", fCharge);

    return Plugin_Continue;
}
