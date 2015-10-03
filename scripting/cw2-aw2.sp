#pragma semicolon 1
#include <tf2_stocks>
#include <sdkhooks>
#include <customweaponstf>
#include <tf2items>
#include <tf2attributes>

#include <chdata>

#define PLUGIN_VERSION "0x01"

public Plugin:myinfo = {
    name = "Custom Weapons: Advanced Weaponiser",
    author = "Chdata & The Slag Gaming Staff",
    description = "Full port of Advanced Weaponiser attributes as a CW2 subplugin",
    version = PLUGIN_VERSION,
    url = "http://steamcommunity.com/groups/tf2data"
};

/* *** Attributes In This Plugin ***

    "meet the sniper combo"                       // Sniper Rifle is "The Walkabout"
    // %f %f %f - Multipliers for each hit in the combo (default is 0.35 0.6 3.0)
*/

// Defines for this plugin

#define STEAMID_CHDATA          "STEAM_0:1:41644167"
#define STEAMID_MECHA           "STEAM_0:0:17402999"
#define STEAMID_CHAWLZ          "STEAM_0:1:16442933"
#define STEAMID_GIRL            "STEAM_0:0:19610706"
#define STEAMID_GAGE            "STEAM_0:1:7484070"
#define STEAMID_SVDL            "STEAM_0:0:16547001"

// Attribute related vars

//#define SOUND_1016_A                        "physics/surfaces/underwater_impact_bullet1.wav"
//#define SOUND_1016_B                        "physics/surfaces/underwater_impact_bullet2.wav"
//#define SOUND_1016_C                        "physics/surfaces/underwater_impact_bullet3.wav"

#define SFX_SNIPER_COMBO_1016_1A                "AdvancedWeaponiser/walkabout_combo_1a.wav"
#define SFX_SNIPER_COMBO_1016_1B                "AdvancedWeaponiser/walkabout_combo_1b.wav"
#define SFX_SNIPER_COMBO_1016_2                 "AdvancedWeaponiser/walkabout_combo_2.wav"
#define SFX_SNIPER_COMBO_1016_3                 "AdvancedWeaponiser/walkabout_combo_3.wav"

static bool:g_bHasSniperCombo1016[TF_MAX_PLAYERS][3];
static g_iSniperCombo1016[TF_MAX_PLAYERS][3];
static bool:g_iSniperComboHit1016[TF_MAX_PLAYERS][3];
static Float:g_flSniperComboMult1016[TF_MAX_PLAYERS][3][3]; // Slot, multiplier

public OnMapStart()
{
    for (new iClient = 1; iClient <= MaxClients; iClient++)
    {
        if (IsClientInGame(iClient))
        {
            OnClientPostAdminCheck(iClient);
        }
    }

    if (IsValidEntity(0))
    {
        new DOWHILE_ENTFOUND(iEnt, "obj_*")
        {
            SDKHook(iEnt, SDKHook_OnTakeDamage, OnTakeDamage_Building);
        } 
    }

    PrepareSound(SFX_SNIPER_COMBO_1016_1A);
    PrepareSound(SFX_SNIPER_COMBO_1016_1B);
    PrepareSound(SFX_SNIPER_COMBO_1016_2);
    PrepareSound(SFX_SNIPER_COMBO_1016_3);
}

public OnClientPostAdminCheck(iClient)
{
    //SDKHook(iClient, SDKHook_PostThinkPost, OnClientPostThinkPost);
    SDKHook(iClient, SDKHook_OnTakeDamage, OnTakeDamage_Player);
    //SDKHook(client, SDKHook_WeaponSwitch, OnWeaponSwitch);
}

public Action:CustomWeaponsTF_OnAddAttribute(iWeapon, iClient, const String:szAttribName[], const String:szSubPlugin[], const String:szValue[])
{
    if (!StrEqual(szSubPlugin, "cw2-aw2")) return Plugin_Continue;

    decl String:szExplode[3][PLATFORM_MAX_PATH];

    new iSlot = GetSlotFromPlayerWeapon(iClient, iWeapon);

    new Action:aReturn = Plugin_Handled; // Default return type.

    if (StrEqual(szAttribName, "meet the sniper combo"))
    {
        g_bHasSniperCombo1016[iClient][iSlot] = true;

        ExplodeString(szValue, " ", szExplode, sizeof(szExplode), sizeof(szExplode[]));

        g_flSniperComboMult1016[iClient][iSlot][0] = StringToFloat(szExplode[0]);
        g_flSniperComboMult1016[iClient][iSlot][1] = StringToFloat(szExplode[1]);
        g_flSniperComboMult1016[iClient][iSlot][2] = StringToFloat(szExplode[2]);
    }
    else
    {
        aReturn = Plugin_Continue;
    }

    return aReturn;
}

public Action:OnTakeDamage_Building(iBuilding, &iAtker, &iInflictor, &Float:flDamage, &iDmgType, &iWeapon, Float:vDmgForce[3], Float:vDmgPos[3], iDmgCustom)
{
    new Action:aReturn = Plugin_Continue;

    new iAtkSlot = -1;

    if (0 < iAtker && iAtker <= MaxClients)
    {
        if (IsValidWeapon(iWeapon))
        {
            iAtkSlot = GetSlotFromPlayerWeapon(iAtker, iWeapon);
        }
    }

    ActionApply(aReturn, OnTakeDamage_Main(iBuilding, iAtker, iInflictor, flDamage, iDmgType, iWeapon, vDmgForce, vDmgPos, iDmgCustom,
        iAtkSlot, true));
    return aReturn;
}

public Action:OnTakeDamage_Player(iVictim, &iAtker, &iInflictor, &Float:flDamage, &iDmgType, &iWeapon, Float:vDmgForce[3], Float:vDmgPos[3], iDmgCustom)
{
    new Action:aReturn = Plugin_Continue;

    //new TFClassType:iAtkClass = TFClass_Unknown;
    //new TFClassType:iVicClass = TFClass_Unknown;
    new iAtkSlot = -1;
    //new iVicSlot = -1;
    //new iDefIndex = -1;

    if (0 < iAtker && iAtker <= MaxClients)
    {
        //iAtkClass = TF2_GetPlayerClass(iAtker);
    
        if (IsValidWeapon(iWeapon))
        {
            iAtkSlot = GetSlotFromPlayerWeapon(iAtker, iWeapon);
            //iDefIndex =  GetEntProp(iWeapon, Prop_Send, "m_iItemDefinitionIndex");
        }
    }

    /*if (0 < iVictim && iVictim <= MaxClients)
    {
        iVicClass = TF2_GetPlayerClass(iVictim);
    
        if (IsValidWeapon(iWeapon))
        {
            iVicSlot = GetSlotFromPlayerWeapon(iVictim, iWeapon);
            //iDefIndex =  GetEntProp(iWeapon, Prop_Send, "m_iItemDefinitionIndex");
        }
    }*/

    ActionApply(aReturn, OnTakeDamage_Main(iVictim, iAtker, iInflictor, flDamage, iDmgType, iWeapon, vDmgForce, vDmgPos, iDmgCustom,
        iAtkSlot, false));
    return aReturn;
}

public Action:OnTakeDamage_Main(iVictim, &iAtker, &iInflictor, &Float:flDamage, &iDmgType, &iWeapon, Float:vDmgForce[3], Float:vDmgPos[3], iDmgCustom,
    iAtkSlot, bool:bBuilding)
{
    if (!IsValidClient(iAtker))
    {
        return Plugin_Continue;
    }

    if (iAtkSlot != -1 && g_bHasSniperCombo1016[iAtker][iAtkSlot] && iAtker != iVictim && flDamage > 0.0)
    {
        g_iSniperComboHit1016[iAtker][iAtkSlot] = true;

        if (bBuilding)
        {
            return Plugin_Continue;
        }

        g_iSniperCombo1016[iAtker][iAtkSlot]++;
        
        decl String:szSound[PLATFORM_MAX_PATH];
        strcopy(szSound, sizeof(szSound), SFX_SNIPER_COMBO_1016_1A);
        
        if (g_iSniperCombo1016[iAtker][iAtkSlot] <= 1)
        {
            if (GetRandomInt(0, 1))
            {
                strcopy(szSound, sizeof(szSound), SFX_SNIPER_COMBO_1016_1B);
            }
            flDamage *= g_flSniperComboMult1016[iAtker][iAtkSlot][0];
        }
        else if (g_iSniperCombo1016[iAtker][iAtkSlot] == 2)
        {
            strcopy(szSound, sizeof(szSound), SFX_SNIPER_COMBO_1016_2);
            flDamage *= g_flSniperComboMult1016[iAtker][iAtkSlot][1];
        }
        else if (g_iSniperCombo1016[iAtker][iAtkSlot] >= 3)
        {
            strcopy(szSound, sizeof(szSound), SFX_SNIPER_COMBO_1016_3);
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

public Action:TF2_CalcIsAttackCritical(iClient, iWeapon, String:szWeaponNAme[], &bool:bResult)
{
    new iSlot = GetSlotFromPlayerWeapon(iClient, iWeapon);
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
    }
}

public OnEntityCreated(iEnt, const String:szClassname[])
{
    if (iEnt > 2048 || !IsValidEnt(iEnt))
    {
        return;
    }

    //g_flEntityCreateTime[iEnt] = GetEngineTime();
    //g_iProjectileBounces[iEnt] = 0;

    if (StrStarts(szClassname, "obj_"))
    {
        CreateTimer(0.3, OnBuildingSpawned, EntIndexToEntRef(iEnt));
    }
}

public Action:OnBuildingSpawned(Handle:hTimer, any:iRef)
{
    new iEnt = EntRefToEntIndex(iRef);
    if (IsValidEnt(iEnt))
    {
        SDKHook(iEnt, SDKHook_OnTakeDamage, OnTakeDamage_Building);
    }
}

public Action:CustomWeaponsTF_PreWeaponSpawned(iClient)
{
    // All of these values are reset before CustomWeaponsTF_OnAddAttribute() is called
    for (new i = 0; i < 3 ; i++)
    {
        g_bHasSniperCombo1016[iClient][i] = false;
        g_iSniperCombo1016[iClient][i] = 0;
    }
}
