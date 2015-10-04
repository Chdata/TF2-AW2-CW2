#define ATTRIBUTE_DAMAGE_BOOST_ON_KILL	1190


public Attribute_1190_Init()
{
    AddRecharge(ATTRIBUTE_DAMAGE_BOOST_ON_KILL, "Spade", 0.0, 100.1, false, false);
}

Attribute_1190_OnDeath(iClient, &iAttacker, &iAssister) 
{
    if (ClientHasAttribute(iAttacker, 2, ATTRIBUTE_DAMAGE_BOOST_ON_KILL))
        {
        if (!IsValidClient(iAttacker)) {PrintToChat(iAttacker, "Attacker is not valid!"); return;}
        if (iClient == iAttacker) {PrintToChat(iAttacker, "Attacker is iClient!"); return;}
        if (IsEntityBuilding(iClient)) {return;}
        if (!IsPlayerAlive(iAttacker)) {PrintToChat(iAttacker, "Attacker is not alive!"); return;}

        AddClientRecharge(iAttacker, ATTRIBUTE_DAMAGE_BOOST_ON_KILL, 20.0);
        PrintToChat(iAttacker, "Maggot squashed! +20 Spade!");
        }
    if (ClientHasAttribute(iAssister, 2, ATTRIBUTE_DAMAGE_BOOST_ON_KILL))
        {
        if (!IsValidClient(iAssister)) return;
        if (iClient == iAssister) return;
        if (IsEntityBuilding(iClient)) return;
        if (!IsPlayerAlive(iAssister)) return;

        AddClientRecharge(iAssister, ATTRIBUTE_DAMAGE_BOOST_ON_KILL, 10.0);
        PrintToChat(iAssister, "Maggot squashed with help! +10 Spade!");
        }

    return;
}


public Action:Attribute_1190_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DAMAGE_BOOST_ON_KILL)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fAdd = GetClientRecharge(iAttacker, ATTRIBUTE_DAMAGE_BOOST_ON_KILL);

    if (IsDamageTypeCrit(iDamageType)) {fAdd *= 3;}

    fDamage += fAdd;
    
    return Plugin_Changed;
}