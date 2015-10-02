#define ATTRIBUTE_DAMAGE_DONE_IS_HEALED      1085

new Float:g_f1085Heal[MAXPLAYERS+1] = 0.0;

public Action:Attribute_1085_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DAMAGE_DONE_IS_HEALED)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fHealed = fDamage * GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DAMAGE_DONE_IS_HEALED);
    g_f1085Heal[iAttacker] += fHealed;
    if (g_f1085Heal[iAttacker] >= 1.0)
    {
        new iHeal = RoundToFloor(g_f1085Heal[iAttacker]);
        if (iHeal >= 1)
        {
            g_f1085Heal[iAttacker] -= float(iHeal);
            new iHealth = GetClientHealth(iAttacker);
            iHealth += iHeal;
            new iOverHeal = GetClientMaxOverHeal(iAttacker);
            if (iHealth > iOverHeal) iHealth = iOverHeal;
            SetEntityHealth(iAttacker, iHealth);
        }
    }
    
    return Plugin_Continue;
}