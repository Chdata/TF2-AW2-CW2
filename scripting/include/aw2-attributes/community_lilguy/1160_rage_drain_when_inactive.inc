#define ATTRIBUTE_RAGE_DRAIN_WHEN_INACTIVE	1160

new g_i1160RageDrain[MAXPLAYERS+1] = 0;
new Float:g_f1160LastHit[MAXPLAYERS+1] = 0.0;

Attribute_1160_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (!ClientHasAttribute(iClient, _, ATTRIBUTE_RAGE_DRAIN_WHEN_INACTIVE)) return iButtons;

	new Float:fRage = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
	if (fRage <= 0.0) return iButtons;

	g_i1160RageDrain[iClient] += 1;

	new Float:fInactive = GetClientAttribute(iClient, _, ATTRIBUTE_RAGE_DRAIN_WHEN_INACTIVE);
	if (GetEngineTime() >= g_f1160LastHit[iClient] + fInactive) {
		//60 ticks for 1 sec, 30 ticks for 0.5 sec
		if (g_i1160RageDrain[iClient] >= 30) {
			fRage -= 1.0;
			if (fRage < 0.0) fRage = 0.0;
			SetEntPropFloat(iClient, Prop_Send, "m_flRageMeter", fRage);
			g_i1160RageDrain[iClient] = 0;

			//Attaching particle to a weapon didn't work
			//new iWeap = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
			AttachParticle(iClient, PARTICLE_HADOKEN_TRAIL, 1.0);
            //girl added this to make the Rage Launcher a little more visually distinct
            }
	}
	return iButtons;
}

public Action:Attribute_1160_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (!ClientHasAttribute(iAttacker, _, ATTRIBUTE_RAGE_DRAIN_WHEN_INACTIVE)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (bBuilding) return Plugin_Continue;

	g_f1160LastHit[iAttacker] = GetEngineTime();

	new Float:fRage = GetEntPropFloat(iAttacker, Prop_Send, "m_flRageMeter");
	if (fRage >= 100.0) {
		SlagInv_AddAchievementProgress(iAttacker, "aw2_ragelauncher");
	}

	return Plugin_Continue;
}
