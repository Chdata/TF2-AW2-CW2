#define ATTRIBUTE_INCREASED_PUSHSCALE       1068

public Action:Attribute_1068_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:vForce[3], Float:vForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (IsAfterDamage(iDamageType)) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_INCREASED_PUSHSCALE)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fScale = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_INCREASED_PUSHSCALE);
    if (fScale == 1.0) return Plugin_Continue;
    
    decl Float:vAng[3], Float:vVelocity[3];
    GetClientEyeAngles(iAttacker, vAng);
    vAng[0] = -40.0;
    AnglesToVelocity(vAng, vVelocity, 200.0 * fScale);
    
    TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vVelocity);
    
    return Plugin_Changed;
}