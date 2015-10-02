#define ATTRIBUTE_CRIT_ON_DISGUISE_REMOVAL          1048


public Action:Attribute_1048_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_CRIT_ON_DISGUISE_REMOVAL)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!g_bWasDisguised[iAttacker]) return Plugin_Continue;
    
    
    new Float:fDistance;
    decl Float:vAttackerPos[3];
    GetClientAbsOrigin(iAttacker, vAttackerPos);
    decl Float:vVictimPos[3];
    GetClientAbsOrigin(iVictim, vVictimPos);
    fDistance = GetVectorDistance(vVictimPos, vAttackerPos);
    if (fDistance <= 350.0)
    {
    ApplyMinicrit(iVictim, iAttacker);
    iDamageType = RemoveCritDamageType(iDamageType);
    fDamage *= GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_CRIT_ON_DISGUISE_REMOVAL);
    }
    
    return Plugin_Changed;
}