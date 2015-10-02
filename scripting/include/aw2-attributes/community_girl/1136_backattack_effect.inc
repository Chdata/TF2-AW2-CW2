// y u indentss

#define ATTRIBUTE_BACKATTACK_EFFECT      1136
new bool:g_bBackEffect1136[MAXPLAYERS+1] = false;

public Action:Attribute_1136_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_BACKATTACK_EFFECT)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (bBuilding) return Plugin_Continue;

    new Float:fAttackerOrigin[3];
    new Float:fVictimOrigin[3]; 
    new Float:fVictimFoward[3];
    new Float:fVictimEyes[3];
    new Float:fAngleDifference;
    new Float:fAngleVector[3];
    GetClientAbsOrigin(iAttacker, fAttackerOrigin);
    GetClientAbsOrigin(iVictim, fVictimOrigin);
    fAttackerOrigin[2] = fVictimOrigin[2];

    GetClientEyeAngles(iVictim, fVictimEyes);
    GetAngleVectors(fVictimEyes, fVictimFoward, NULL_VECTOR, NULL_VECTOR);
    MakeVectorFromPoints(fVictimOrigin, fAttackerOrigin, fAngleVector);
    NormalizeVector(fAngleVector, fAngleVector);
    fAngleDifference = GetVectorDotProduct(fVictimFoward, fAngleVector);
    EmitSoundToAll(SOUND_SUPRISE_SPY, iAttacker);

    if (fAngleDifference <= 0.1) 
	{
		g_bBackEffect1136[iAttacker] = true;
    }
	
    if (fAngleDifference > 0.1)
	{
		g_bBackEffect1136[iAttacker] = false;
	}
    if (g_bBackEffect1136[iAttacker] == true)
	{
		new Float:Cond = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_BACKATTACK_EFFECT);
		
		if (Cond <= 1.0)
			{
				iDamageType = MakeCritDamageType(iDamageType);
			}
		else if (Cond == 2.0)
			{
				TF2_AddCondition(iVictim, TFCond_Jarated, 5.0);
			}
		else if (Cond == 3.0)
			{
				TF2_AddCondition(iVictim, TFCond_Milked, 5.0);
			}
		else if (Cond == 4.0)
			{
				TF2_IgnitePlayer(iAttacker, iVictim);
			}
		else if (Cond == 5.0)
			{
				TF2_AddCondition(iVictim, TFCond_Bleeding, 5.0);
			}
		else if (Cond == 6.0)
			{
				TF2_AddCondition(iVictim, TFCond_MarkedForDeath, 5.0);
			}
		else if (Cond == 7.0)
			{
				TF2_AddCondition(iAttacker, TFCond_SpeedBuffAlly, 5.0);
			}
		else if (Cond == 8.0)
			{
				ApplyMinicrit(iVictim, iAttacker);
				iDamageType = RemoveCritDamageType(iDamageType);
				fDamage *= 1.35;
			}
	}
    return Plugin_Changed;
}