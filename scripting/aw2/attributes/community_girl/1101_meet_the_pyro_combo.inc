#define ATTRIBUTE_MEET_THE_PYRO_COMBO         1101

#define DMGBONUS_1101_A                0.80
#define DMGBONUS_1101_B                0.90
#define DMGBONUS_1101_C                1.35

new g_iPyroCombo1101[MAXPLAYERS+1] = 0;
new bool:g_iPyroComboHit1101[MAXPLAYERS+1] = false;

Attribute_1101_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEET_THE_PYRO_COMBO)) return;
    g_iPyroCombo1101[iClient] = 0;
}

Attribute_1101_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEET_THE_PYRO_COMBO)) return;
    if (g_iPyroCombo1101[iClient] > 0) 
	{
        g_iPyroComboHit1101[iClient] = false;
        CreateTimer(0.4, Attribute_1101_Expire, iClient);
    }
}
public Action:Attribute_1101_Expire(Handle:hTimer, any:iClient) {
    if (!g_iPyroComboHit1101[iClient]) {
        g_iPyroCombo1101[iClient] = 0;
    }
}
public Action:Attribute_1101_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_MEET_THE_PYRO_COMBO)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (IsAfterDamage(iDamageType)) return Plugin_Continue;
    
    g_iPyroComboHit1101[iAttacker] = true;
    if (bBuilding) return Plugin_Continue;
    g_iPyroCombo1101[iAttacker]++;
    
    if (g_iPyroCombo1101[iAttacker] <= 1) 
	{ 
        fDamage *= DMGBONUS_1101_A;
    }
    else if (g_iPyroCombo1101[iAttacker] == 2) 
	{
        fDamage *= DMGBONUS_1101_B;
    }
    else if (g_iPyroCombo1101[iAttacker] >= 3) 
	{
    ApplyMinicrit(iVictim, iAttacker);
    iDamageType = RemoveCritDamageType(iDamageType);
    fDamage *= DMGBONUS_1101_C;
    TF2_IgnitePlayer(iVictim, iAttacker);
    g_iPyroCombo1101[iAttacker] = 0;
    }
    
    return Plugin_Changed;
}
