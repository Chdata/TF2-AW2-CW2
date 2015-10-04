#define ATTRIBUTE_EVASIVENESS_ON_HIT		 1007

public Attribute_1007_Init()
{
	AddRecharge(ATTRIBUTE_EVASIVENESS_ON_HIT, "Evasiveness", _, _, _, false);
}

public Action:Attribute_1007_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	if (ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_EVASIVENESS_ON_HIT))
	{
		AddClientRecharge(iAttacker, ATTRIBUTE_EVASIVENESS_ON_HIT, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_EVASIVENESS_ON_HIT));
	}
	if (ClientHasAttribute(iVictim, _, ATTRIBUTE_EVASIVENESS_ON_HIT) && iSlot != 2)
	{
		new Float:fSubtract = GetClientRecharge(iVictim, ATTRIBUTE_EVASIVENESS_ON_HIT);
		if (fSubtract > 0.0)
		{
			if (fDamage < fSubtract) fSubtract = fDamage;
			
			AddClientRecharge(iVictim, ATTRIBUTE_EVASIVENESS_ON_HIT, fSubtract * -1.0);
			
			fDamage -= fSubtract;
			if (fDamage <= 0.0)
			{
				decl Float:vOrigin[3];
				GetClientEyePosition(iVictim, vOrigin);
				vOrigin[2] += 2.0;
				TE_ParticleFromClient(iVictim, "miss_text", vOrigin);
			}
			if (!DamageWillKill(iVictim, fDamage, true))
			{
				if (GetClientHealth(iVictim) >= 125) SlagInv_AddAchievementProgress(iAttacker, "aw2_hax");
			}
			return Plugin_Changed;
		}
	}
	
	return Plugin_Continue;
}