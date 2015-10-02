#define ATTRIBUTE_HEADSHOTGIB            1139

public Action:Attribute_1139_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_HEADSHOTGIB)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (iDamageType == TF_DMG_RIFLE_CRIT)
    {
    NormalizeVector(fForce, fForce);
    if (fForce[2] < 0.2) fForce[2] = 0.2;
    
    new Float:fScale = fDamage*15.0;
    
    if (DamageWillKill(iVictim, fDamage, true)) {
    fScale *= 100.0;
    }
    if (fScale < 100.0) fScale = 100.0;
    ScaleVector(fForce, fScale);
    if (fForce[2] < 320.0 && fDamage >= 10.0) fForce[2] = 320.0;
    decl Float:vClientVelocity[3];
    GetVelocity(iVictim, vClientVelocity);
    AddVectors(vClientVelocity, fForce, vClientVelocity);
    TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vClientVelocity);
    }
    return Plugin_Changed;
    
}