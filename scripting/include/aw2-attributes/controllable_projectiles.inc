#define ATTRIBUTE_CONTROLLABLE_PROJECTILES          1018

#define CONTROLLABLE_PROJECTILE_DELAY               0.05

Attribute_1018_OnProjectile(iEntity, &iClient, &iSlot)
{
    if (!IsValidClient(iClient)) return;
    
    new Float:fLife = GetEntityLife(iEntity);
    fLife -= CONTROLLABLE_PROJECTILE_DELAY;
    //PrintToChatAll("Life: %.2f", fLife);
    if (fLife < 0.0) return;
    
    decl Float:vRocketOrigin[3];
    GetEntPropVector(iEntity, Prop_Data, "m_vecAbsOrigin", vRocketOrigin);
    decl Float:vTargetOrigin[3];
    GetClientPointPosition(iClient, vTargetOrigin, MASK_VISIBLE);
    
    //new Float:fDistance = GetVectorDistance(vRocketOrigin, vTargetOrigin) / 50.0;
    
    decl Float:vRocketVelocity[3];
    GetEntPropVector(iEntity, Prop_Data, "m_vecAbsVelocity", vRocketVelocity);
    new Float:fRocketSpeed = GetVectorLength(vRocketVelocity);
    
    decl Float:vDifference[3];
    SubtractVectors(vTargetOrigin, vRocketOrigin, vDifference);
    
    // middle += velocity
    // (aka becomes less accurate)
    new Float:fBase = GetClientAttribute(iClient, iSlot, ATTRIBUTE_CONTROLLABLE_PROJECTILES);
    new Float:fInaccuracy = fBase - fLife*150.0;
    if (fInaccuracy < 0.0) fInaccuracy = 0.0;
    if (fInaccuracy > 400.0) fInaccuracy = 400.0;
    NormalizeVector(vDifference, vDifference);
    ScaleVector(vDifference, fInaccuracy);
    
    AddVectors(vRocketVelocity, vDifference, vDifference);
    NormalizeVector(vDifference, vDifference);
    
    decl Float:fRocketAngle[3];
    GetVectorAngles(vDifference, fRocketAngle);
    SetEntPropVector(iEntity, Prop_Data, "m_angRotation", fRocketAngle);

    ScaleVector(vDifference, fRocketSpeed);
    SetEntPropVector(iEntity, Prop_Data, "m_vecAbsVelocity", vDifference);
    
    //PrintToChat(iClient, "baah");
}