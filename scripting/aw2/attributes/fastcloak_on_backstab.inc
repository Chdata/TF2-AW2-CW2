#define ATTRIBUTE_FASTCLOAK_ON_BACKSTAB             1062

public Action:Attribute_1062_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_FASTCLOAK_ON_BACKSTAB)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!IsDamageTypeCrit(iDamageType)) return Plugin_Continue;
    
    if (ClientHasAttribute(iAttacker, _, ATTRIBUTE_CLOAK_IS_HOOK))
    {
        new Float:vAngles[3];
        vAngles[0] = -90.0;
        if (CloakIsHookInit(iAttacker, vAngles)) return Plugin_Continue;
        vAngles[0] = -45.0;
        for (new i = 0; i <= 7; i++)
        {
            vAngles[1] = float(i) * 45.0;
            if (CloakIsHookInit(iAttacker, vAngles)) return Plugin_Continue;
        }
        return Plugin_Continue;
    }
    
    FastCloak(iAttacker);
    
    return Plugin_Continue;
}