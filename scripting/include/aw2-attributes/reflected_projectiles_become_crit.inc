#define ATTRIBUTE_REFLECTED_PROJECTILES_BECOMES_CRIT       1067

Attribute_1067_OnProjectile(iEntity, &iClient, &iSlot)
{
    new iDeflector = GetDeflector(iEntity);
    if (!IsValidClient(iDeflector)) return;
    
    new iSlotDeflector = GetClientSlot(iDeflector);
    if (!ClientHasAttribute(iDeflector, iSlotDeflector, ATTRIBUTE_REFLECTED_PROJECTILES_BECOMES_CRIT)) return;
    
    if (IsClassname(iEntity, "tf_projectile_energy_ball")) return;
    
    // already crit
    if (GetEntProp(iEntity, Prop_Send, "m_bCritical") >= 1) return;
    
    SetEntProp(iEntity, Prop_Send, "m_bCritical", 1);
    SetEntProp(iEntity, Prop_Send, "m_nSkin", GetClientTeam(iDeflector));
}