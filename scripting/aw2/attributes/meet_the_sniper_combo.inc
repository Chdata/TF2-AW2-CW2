//Decided to nerf the Walkabout slightly, it now deals far less damage during the initial combo-increase. This should incentivize switching to another weapon or gambling on the three hit combo in close range, instead of retaining most of your no-scope damage.

//#define ATTRIBUTE_MEET_THE_SNIPER_COMBO         1016

/*static const String:s_szMisfired[][] = {
    "physics/surfaces/underwater_impact_bullet1.wav", // SOUND_1016_A
    "physics/surfaces/underwater_impact_bullet2.wav", // SOUND_1016_B
    "physics/surfaces/underwater_impact_bullet3.wav"  // SOUND_1016_C
};*/

#define SNIPER_COMBO_1016_1A                "AdvancedWeaponiser/walkabout_combo_1a.wav"
#define SNIPER_COMBO_1016_1B                "AdvancedWeaponiser/walkabout_combo_1b.wav"
#define SNIPER_COMBO_1016_2                 "AdvancedWeaponiser/walkabout_combo_2.wav"
#define SNIPER_COMBO_1016_3                 "AdvancedWeaponiser/walkabout_combo_3.wav"

new bool:g_bHasSniperCombo1016[TF_MAX_PLAYERS][3];
new g_iSniperCombo1016[TF_MAX_PLAYERS][3];
new bool:g_iSniperComboHit1016[TF_MAX_PLAYERS][3];
new Float:g_flSniperComboMult1016[TF_MAX_PLAYERS][3][3]; // Slot, multiplier

Attribute_1016_Precache()
{
    PrepareSound(SNIPER_COMBO_1016_1A);
    PrepareSound(SNIPER_COMBO_1016_1B);
    PrepareSound(SNIPER_COMBO_1016_2);
    PrepareSound(SNIPER_COMBO_1016_3);

    //PrecacheSoundList(s_szMisfired, sizeof(s_szMisfired));
}

Attribute_1016_OnInventory(iClient, iSlot)
{
    g_bHasSniperCombo1016[iClient][iSlot] = false;
    g_iSniperCombo1016[iClient][iSlot] = 0;
}

Attribute_1016_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (iSlot != -1 && g_iSniperCombo1016[iClient][iSlot] > 0)
    {
        g_iSniperComboHit1016[iClient][iSlot] = false;

        new Handle:hData = CreateDataPack();
        WritePackCell(hData, iClient);
        WritePackCell(hData, iSlot);
        RequestFrame(Frame_Attribute_1016_Expire, hData);
    }
}

public Frame_Attribute_1016_Expire(any:Pack)
{
    ResetPack(Handle:Pack);
    new iClient = ReadPackCell(Handle:Pack);
    new iSlot = ReadPackCell(Handle:Pack);
    CloseHandle(Handle:Pack);
    
    if (!g_iSniperComboHit1016[iClient][iSlot])
    {
        g_iSniperCombo1016[iClient][iSlot] = 0;

        //decl String:szSound[PLATFORM_MAX_PATH];
        //strcopy(szSound, sizeof(szSound), s_szMisfired[GetRandomInt(0, sizeof(s_szMisfired)-1)]);
        //EmitSoundToClient(iClient, szSound);
    }
}

public Action:Attribute_1016_OnTakeDamage(iVictim, &iAtker, &iInflictor, &Float:flDamage, &iDmgType, &iWeapon, Float:vDmgForce[3], Float:vDmgPos[3], iDmgCustom,
    iAtkSlot, bool:bBuilding)
{
    if (iAtkSlot != -1 && g_bHasSniperCombo1016[iAtker][iAtkSlot] && iAtker != iVictim && flDamage > 0.0)
    {
        g_iSniperComboHit1016[iAtker][iAtkSlot] = true;

        if (bBuilding)
        {
            return Plugin_Continue;
        }

        g_iSniperCombo1016[iAtker][iAtkSlot]++;
        
        decl String:szSound[PLATFORM_MAX_PATH];
        strcopy(szSound, sizeof(szSound), SNIPER_COMBO_1016_1A);
        
        if (g_iSniperCombo1016[iAtker][iAtkSlot] <= 1)
        {
            if (GetRandomInt(0, 1))
            {
                strcopy(szSound, sizeof(szSound), SNIPER_COMBO_1016_1B);
            }
            flDamage *= g_flSniperComboMult1016[iAtker][iAtkSlot][0];
        }
        else if (g_iSniperCombo1016[iAtker][iAtkSlot] == 2)
        {
            strcopy(szSound, sizeof(szSound), SNIPER_COMBO_1016_2);
            flDamage *= g_flSniperComboMult1016[iAtker][iAtkSlot][1];
        }
        else if (g_iSniperCombo1016[iAtker][iAtkSlot] >= 3)
        {
            strcopy(szSound, sizeof(szSound), SNIPER_COMBO_1016_3);
            iDmgType |= DMG_CRIT;
            flDamage *= g_flSniperComboMult1016[iAtker][iAtkSlot][2];
            g_iSniperCombo1016[iAtker][iAtkSlot] = 0;
        }

        if (ShouldReveal(iVictim))
        {
            EmitSoundToClient(iAtker, szSound);
        }

        return Plugin_Changed;
    }

    return Plugin_Continue;
}

stock bool:IsDisguised(iClient)
{
    new TFClassType:iClass = TFClassType:GetEntProp(iClient, Prop_Send, "m_nDisguiseClass");
    return (iClass != TFClass_Unknown);
}

stock bool:ShouldReveal(iClient)
{
    if (TF2_IsPlayerInCondition(iClient, TFCond_Cloaked))
    {
        return true;
    }

    if (IsDisguised(iClient))
    {
        return false;
    }

    return true;
}
