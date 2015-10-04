#define ATTRIBUTE_REVERSE_SCALING      1142

public Action:Attribute_1142_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_REVERSE_SCALING)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;

    new Float:fDistance;
    decl Float:vClientPos[3];
    GetClientAbsOrigin(iAttacker, vClientPos);
    decl Float:vVictimPos[3];
    GetClientAbsOrigin(iVictim, vVictimPos);
    fDistance = GetVectorDistance(vVictimPos, vClientPos);
    
    fDistance *= 0.003;
    fDamage *= fDistance;
    
    return Plugin_Changed;
}