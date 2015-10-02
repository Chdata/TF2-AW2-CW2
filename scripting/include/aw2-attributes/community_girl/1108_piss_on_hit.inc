#define ATTRIBUTE_PISS_ON_HIT         1108

public Action:Attribute_1108_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_PISS_ON_HIT)) return Plugin_Continue;
    if (fDamage <= 3.5) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;
    
    new Handle:hData = CreateDataPack();
    WritePackCell(hData, iVictim);
    WritePackFloat(hData, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_PISS_ON_HIT));
    CreateTimer(0.1, Attribute_1108_ApplyJarate, hData);

    return Plugin_Continue;
}

public Action:Attribute_1108_ApplyJarate(Handle:hTimer, Handle:hData)
{
    ResetPack(hData);
    new iVictim = ReadPackCell(hData);
    new Float:fDuration = ReadPackFloat(hData);
    if (IsValidClient(iVictim) && IsPlayerAlive(iVictim)) {
        TF2_AddCondition(iVictim, TFCond_Jarated, fDuration);
    }
    CloseHandle(hData);
}
