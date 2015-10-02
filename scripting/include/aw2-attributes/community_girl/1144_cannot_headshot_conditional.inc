#define ATTRIBUTE_CANNOTHEADSHOT_BEFOREBODYSHOT       1144

new bool:g_bTookDamage1144[MAXPLAYERS+1] = false;
new bool:g_bTookHeadShot1144[MAXPLAYERS+1] = false;
new g_iLastTarget1144[MAXPLAYERS+1] = 0;


public Action:Attribute_1144_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_CANNOTHEADSHOT_BEFOREBODYSHOT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (iDamageType == TF_DMG_RIFLE_CRIT)
    {
    if (iVictim != g_iLastTarget1144[iAttacker])
    {
        if (!g_bTookHeadShot1144[iAttacker])
        {
            if (g_bTookDamage1144[iAttacker])
            {
            g_bTookHeadShot1144[iAttacker] = false;
            g_bTookDamage1144[iAttacker] = true;
            }
            g_bTookDamage1144[iAttacker] = false;
            g_bTookHeadShot1144[iAttacker] = true;
            iDamageType = TF_DMG_RIFLE_CHARGED;
        }
        g_bTookDamage1144[iAttacker] = true;
        iDamageType = TF_DMG_RIFLE_CHARGED;
    }
    }
    
    g_bTookDamage1144[iAttacker] = true;
    g_bTookHeadShot1144[iAttacker] = false;
    g_iLastTarget1144[iAttacker] = iVictim;
    
    return Plugin_Changed;
}

Attribute_1144_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!g_iLastTarget1144[iClient]) return iButtons;
    if (!IsValidClient(iClient)) return iButtons;
    
    AttachParticle(iClient, PARTICLE_ORBITING_SKULL, 0.2);
    
    return iButtons;
 }