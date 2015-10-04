#define ATTRIBUTE_TAUNT_CHANGES_MODE            1135

new bool:g_bMode1135[MAXPLAYERS+1] = false;

public Attribute_1135_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Taunting) return;
    decl String:strActiveWeapon[32];
    GetClientWeapon(iClient, strActiveWeapon, sizeof(strActiveWeapon));
    new iSlot = GetWeaponSlot(strActiveWeapon);
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_TAUNT_CHANGES_MODE)) return;

    if (g_bMode1135[iClient])
    {
        g_bMode1135[iClient] = false;
    }
    else if (!g_bMode1135[iClient])
    {
        g_bMode1135[iClient] = true;
    }
}

public Action:Attribute_1135_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_TAUNT_CHANGES_MODE)) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    new weaponentity = GetEntPropEnt(iAttacker, Prop_Send, "m_hActiveWeapon");
	
    if (g_bMode1135[iAttacker])
    {
        iDamageType = MakeCritDamageType(iDamageType);
        fDamage *=0.3;
        new Float:firTime = (GetGameTime() + 0.58);
        SetEntPropFloat(weaponentity, Prop_Send, "m_flNextPrimaryAttack", firTime);
    }
    else if (!g_bMode1135[iAttacker])
    {
        new Float:firTime = (GetGameTime() + 0.46);
        SetEntPropFloat(weaponentity, Prop_Send, "m_flNextPrimaryAttack", firTime);
    }
    return Plugin_Changed;
}