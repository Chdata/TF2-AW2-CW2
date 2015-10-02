#define ATTRIBUTE_PROJECTILE_SPEED		  1118

Attribute_1118_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_PROJECTILE_SPEED)) return;
    
    new Float:fOrigin[3];
    new Float:fVelocity[3];
    new Float:fRotation[3];
    new Float:fProjectileSpeed1118 = GetClientAttribute(iClient, iSlot, ATTRIBUTE_PROJECTILE_SPEED);
    GetEntPropVector(iEntity, Prop_Data, "m_vecOrigin", fOrigin);
    GetEntPropVector(iEntity, Prop_Data, "m_vecVelocity", fVelocity);
    GetEntPropVector(iEntity, Prop_Data, "m_angRotation", fRotation);
    NormalizeVector(fVelocity, fVelocity);
    ScaleVector(fVelocity, fProjectileSpeed1118);
    TeleportEntity(iEntity, fOrigin, fRotation, fVelocity);
}