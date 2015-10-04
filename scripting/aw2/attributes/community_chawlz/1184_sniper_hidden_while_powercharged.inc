#define ATTRIBUTE_HIDDEN_WHILE_POWERCHARGED          1184

new bool:g_bIsBlinking1184[MAXPLAYERS+1] = false;
//new bool:g_bBeingWatched1184[MAXPLAYERS+1] = false;
//new g_iLookedAt1184[MAXPLAYERS+1] = 0;
//new g_iSniperLookTime1184[MAXPLAYERS+1] = 0;

Attribute_1184_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {

    //Stolen code that makes you visible while looked at probably
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_HIDDEN_WHILE_POWERCHARGED))
//    {
//	new iTarget = GetClientAimTarget(iClient, false);
//	if (iTarget <= -1) return iButtons;
//	if (!IsValidClient(iTarget)) return iButtons;
//        if (!ClientHasAttribute(iTarget, _, ATTRIBUTE_HIDDEN_WHILE_POWERCHARGED)) return iButtons;
//
//	new iTeam = GetClientTeam(iClient);
//	if (GetClientTeam(iTarget) == iTeam) return iButtons;
//
//        g_bBeingWatched1184[iTarget] = true;
//
//	g_iSniperLookTime1184[iTarget] += 1;
//
//	if (g_iSniperLookTime1178[iTarget] >= 60)
//        {
//                //Bonus to look penalty if enemy is zoomed
//                if (g_iLookedAt1184[iTarget] << 15)
//                {
//                if (TF2_IsPlayerInCondition(iTarget, TFCond_Zoomed)){g_iLookedAt1184[iTarget] += 3;}
//		g_iLookedAt1184[iTarget] += 2;
//                }
//		g_iSniperLookTime1178[iTarget] = 0;
//                PrintToChat(iTarget, "being watched");
//        }
//
         return iButtons;
//    }

    if (!TF2_IsPlayerInCondition(iClient, TFCond_Zoomed)){HideClientWearables(iClient, false);HideEntity(iClient, false); return iButtons;}

    new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
    new Float:fCharge = GetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage");

    if (fCharge >= GetClientAttribute(iClient, _, ATTRIBUTE_HIDDEN_WHILE_POWERCHARGED)*100.0)
        {
        HideClientWearables(iClient, true);
        HideEntity(iClient, true);
        }
    else
        {
        HideClientWearables(iClient, false);
        HideEntity(iClient, false);
        }

    if (!TF2_IsPlayerInCondition(iClient, TFCond_Zoomed))
        {
        HideClientWearables(iClient, false);
        HideEntity(iClient, false);
        }

    if (g_bIsBlinking1184[iClient] == true)
        {
        HideClientWearables(iClient, false);
        HideEntity(iClient, false);
        }

//    if (g_iLookedAt1184[iClient] >= 5)
//        {
//        HideClientWearables(iClient, false);
//        HideEntity(iClient, false);
//        }

//    if (g_bBeingWatched1184[iClient])
//        {
//        g_iLookedAt1184[iClient] -= 1;
//        g_bBeingWatched1184[iClient] = false;
//        }
    return iButtons;
}

public Action:Attribute_1184_Timer(Handle:hTimer, any:iClient) 
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_HIDDEN_WHILE_POWERCHARGED)) return;
    
    g_bIsBlinking1184[iClient] = false;
}

public Action:Attribute_1184_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (!ClientHasAttribute(iVictim, 0, ATTRIBUTE_HIDDEN_WHILE_POWERCHARGED)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (!TF2_IsPlayerInCondition(iVictim, TFCond_Zoomed)) return Plugin_Continue;

    CreateTimer(0.3, Attribute_1184_Timer, iVictim);
    g_bIsBlinking1184[iVictim] = true;

    return Plugin_Continue;
}
