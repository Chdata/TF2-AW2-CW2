#pragma semicolon 1
#include <tf2_stocks>
#include <sdkhooks>
#include <customweaponstf>
#include <tf2items>
#include <tf2attributes>

#include <chdata>

#include aw2/attributes.inc

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

    Attribute_1016_Precache();
    Attribute_1160_Precache();
}

public OnClientPostAdminCheck(iClient)
{
    SDKHook(iClient, SDKHook_PostThinkPost, OnClientPostThinkPost);
    SDKHook(iClient, SDKHook_OnTakeDamage, OnTakeDamage_Player);
    //SDKHook(client, SDKHook_WeaponSwitch, OnWeaponSwitch);
}

public Action:CustomWeaponsTF_PreWeaponSpawned(iClient, iSlot)
{
    // All of these values are reset before CustomWeaponsTF_OnAddAttribute() is called
    Attribute_1016_OnInventory(iClient, iSlot);
    Attribute_1160_OnInventory(iClient, iSlot);
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
    else if (StrEqual(szAttribName, "inactivity drains rage"))
    {
        g_flRageDrainWhenInactiveFor[iClient] = StringToFloat(szValue);
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

public OnClientPostThinkPost(iClient)
{
    Attribute_1160_Prethink(iClient);
}

public Action:OnTakeDamage_Main(iVictim, &iAtker, &iInflictor, &Float:flDamage, &iDmgType, &iWeapon, Float:vDmgForce[3], Float:vDmgPos[3], iDmgCustom,
    iAtkSlot, bool:bBuilding)
{
    if (!IsValidClient(iAtker))
    {
        return Plugin_Continue;
    }

    new Action:aReturn = Plugin_Continue;

    ActionApply(aReturn, Attribute_1016_OnTakeDamage(iVictim, iAtker, iInflictor, flDamage, iDmgType, iWeapon, vDmgForce, vDmgPos, iDmgCustom, iAtkSlot, bBuilding));
    ActionApply(aReturn, Attribute_1160_OnTakeDamage(iVictim, iAtker, iInflictor, flDamage, iDmgType, iWeapon, vDmgForce, vDmgPos, iDmgCustom, iAtkSlot, bBuilding));

    return aReturn;
}

public Action:TF2_CalcIsAttackCritical(iClient, iWeapon, String:szWeaponNAme[], &bool:bResult)
{
    new iSlot = GetSlotFromPlayerWeapon(iClient, iWeapon);

    Attribute_1016_OnAttack(iClient, iSlot, bResult);
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
