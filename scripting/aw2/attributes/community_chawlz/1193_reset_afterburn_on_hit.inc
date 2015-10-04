#define ATTRIBUTE_RESET_AFTERBURN_ON_HIT		1193

new g_iAchBoilerTimer1193[MAXPLAYERS+1] = 0;
new g_iAchBoilerBurner1193[MAXPLAYERS+1] = 0;

Attribute_1193_Precache()
{
	SuperPrecacheSound(SOUND_FLAME_ENGULF);
}

public Action:Attribute_1193_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_RESET_AFTERBURN_ON_HIT))
		{
		if (ClientHasAttribute(iAttacker, 2, ATTRIBUTE_RESET_AFTERBURN_ON_HIT))
			{
			if (g_iAchBoilerBurner1193[iVictim] == iAttacker) g_iAchBoilerTimer1193[iVictim] = 0;
			}
		return Plugin_Continue;
		}
	if (bBuilding) return Plugin_Continue;
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (!TF2_IsPlayerInCondition(iVictim, TFCond_OnFire)) return Plugin_Continue;
	if (IsAfterDamage(iDamageType))
		{
		if (g_iAchBoilerBurner1193[iVictim] != iAttacker)
			{
			g_iAchBoilerBurner1193[iVictim] = 0;
			g_iAchBoilerTimer1193[iVictim] = 0;
			}
		else
			{
			g_iAchBoilerTimer1193[iVictim] += 1;
			if (g_iAchBoilerTimer1193[iVictim] >= 30)
				SlagInv_AddAchievementProgress(iAttacker, "aw2_boilerbuss");
			}
		return Plugin_Continue;
		}

	TF2_IgnitePlayer(iVictim, iAttacker);
	EmitSoundToAll(SOUND_FLAME_ENGULF, iVictim, _, _, SND_CHANGEVOL, SNDVOL_NORMAL*1.5);

	g_iAchBoilerBurner1193[iVictim] = iAttacker;
	
	return Plugin_Continue;
}

public Attribute_1193_OnConditionRemoved(iClient, TFCond:condition)
{
	if (!IsValidClient(iClient)) return;
	if (condition != TFCond_OnFire) return;
	if (g_iAchBoilerTimer1193[iClient] == 0) return;

	g_iAchBoilerBurner1193[iClient] = 0;
	g_iAchBoilerTimer1193[iClient] = 0;
}
