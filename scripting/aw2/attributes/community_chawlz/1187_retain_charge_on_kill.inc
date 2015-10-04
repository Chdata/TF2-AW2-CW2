#define ATTRIBUTE_RETAIN_CHARGE_ON_KILL     1187

new Float:g_flRetainedPowerCharge1187[MAXPLAYERS+1] = 0.0;
new bool:g_bHasRecievedPowerCharge1187[MAXPLAYERS+1] = false;
new bool:g_bDidShotKill1187[MAXPLAYERS+1] = false;

Attribute_1187_OnDeath(iClient, &iAttacker, &iAssister, iSlot) 
{
    if (!IsValidClient(iAttacker)) return;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_RETAIN_CHARGE_ON_KILL)) return;
    if (iClient == iAttacker) return;
    if (IsEntityBuilding(iClient)) return;
    if (!IsPlayerAlive(iAttacker)) return;
    //if (!TF2_IsPlayerInCondition(iAttacker, TFCond_Zoomed)) return;
    
    g_bDidShotKill1187[iAttacker] = true;
    PrintToChat(iAttacker, "bopt");

    return;
}

Attribute_1187_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_RETAIN_CHARGE_ON_KILL)) return;

    return;
}

Attribute_1187_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_RETAIN_CHARGE_ON_KILL)) return iButtons;
    if (!TF2_IsPlayerInCondition(iClient, TFCond_Zoomed)) return iButtons;
    if (g_bHasRecievedPowerCharge1187[iClient] == false)
        {
        new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
        g_flRetainedPowerCharge1187[iClient] = GetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage");
        return iButtons;
        }
    if (g_bDidShotKill1187[iClient] == false) return iButtons;

    new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");

    SetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage", g_flRetainedPowerCharge1187[iClient]);

    PrintToChat(iClient, "Charge recovered: %.2f", g_flRetainedPowerCharge1187[iClient]);

    g_flRetainedPowerCharge1187[iClient] = 0.0;
    g_bHasRecievedPowerCharge1187[iClient] = false;
    g_bDidShotKill1187[iClient] = false;

    return iButtons;
}

public Attribute_1187_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_RETAIN_CHARGE_ON_KILL)) return;
    if (condition != TFCond_Zoomed) return;

    //new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
    //new Float:fCharge = GetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage");
    new Float:fMaxCharge = GetClientAttribute(iClient, _, ATTRIBUTE_HIDDEN_WHILE_POWERCHARGED)*150.0;
   
    if (g_flRetainedPowerCharge1187[iClient] > fMaxCharge)
//        {
//        g_flRetainedPowerCharge1187[iClient] = fCharge;
//        }
//    else
        {
        g_flRetainedPowerCharge1187[iClient] = fMaxCharge;
        }

    PrintToChat(iClient, "Remaining charge: %.2f", g_flRetainedPowerCharge1187[iClient]);
    g_bHasRecievedPowerCharge1187[iClient] = true;

    return;
}