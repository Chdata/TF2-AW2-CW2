new Float:g_flRageDrainWhenInactiveFor[TF_MAX_PLAYERS]; // Inits to -1.0
new g_i1160RageDrain[TF_MAX_PLAYERS] = 0;
new Float:g_fl1160LastHit[TF_MAX_PLAYERS] = 0.0;

Attribute_1160_Precache()
{
	PrecacheParticleSystem(PARTICLE_HADOKEN_TRAIL);
}

stock Attribute_1160_OnInventory(iClient, iSlot)
{
    g_flRageDrainWhenInactiveFor[iClient] = -1.0;
}

Attribute_1160_Prethink(iClient) // , &iButtons, &iSlot, &iButtonsLast
{
	if (g_flRageDrainWhenInactiveFor[iClient] > 0.0)
    {
        new Float:flRage = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
        if (flRage <= 0.0)
        {
            return;
        }

        g_i1160RageDrain[iClient] += 1;

        if (GetEngineTime() >= g_fl1160LastHit[iClient] + g_flRageDrainWhenInactiveFor[iClient])
        {
            //60 ticks for 1 sec, 30 ticks for 0.5 sec
            if (g_i1160RageDrain[iClient] >= 30)
            {
                flRage -= 1.0;
                if (flRage < 0.0)
                {
                    flRage = 0.0;
                }
                SetEntPropFloat(iClient, Prop_Send, "m_flRageMeter", flRage);
                g_i1160RageDrain[iClient] = 0;

                //Attaching particle to a weapon didn't work
                //new iWeap = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
                AttachParticle(iClient, PARTICLE_HADOKEN_TRAIL, 1.0);
                //girl added this to make the Rage Launcher a little more visually distinct
            }
        }
    }
}

public Action:Attribute_1160_OnTakeDamage(iVictim, &iAtker, &iInflictor, &Float:flDamage, &iDmgType, &iWeapon, Float:vDmgForce[3], Float:vDmgPos[3], iDmgCustom,
    iAtkSlot, bool:bBuilding)
{
    if (g_flRageDrainWhenInactiveFor[iAtker] > 0.0)
    {
        if (iAtker == iVictim) return Plugin_Continue;
        if (flDamage <= 0.0) return Plugin_Continue;
        if (bBuilding) return Plugin_Continue;

        g_fl1160LastHit[iAtker] = GetEngineTime();
    }
    return Plugin_Continue;
}
