#define ATTRIBUTE_SOUND_WHILE_ACTIVE         1086

new String:g_str1086Sounds[][PLATFORM_MAX_PATH] = {
    "AdvancedWeaponiser/trumpet_danger_1.wav",
    "AdvancedWeaponiser/trumpet_danger_2.wav",
    "AdvancedWeaponiser/trumpet_danger_3.wav",
    "AdvancedWeaponiser/trumpet_danger_4.wav"
};

new g_i1086Emitting[MAXPLAYERS+1] = -1;
new Float:g_f1086LastFire[MAXPLAYERS+1] = 0.0;
new String:g_str1086LastSound[MAXPLAYERS+1][PLATFORM_MAX_PATH];

Attribute_1086_Precache()
{    
    for (new i = 0; i < sizeof(g_str1086Sounds); i++)
    {
        SuperPrecacheSound(g_str1086Sounds[i]);
    }
}

Attributes_1086_Stop()
{    
    for (new iClient = 0; iClient <= MaxClients; iClient++)
    {
        if (IsValidClient(iClient) && g_i1086Emitting[iClient] >= 0)
        {
            StopSound(iClient, SNDCHAN_WEAPON, g_str1086LastSound[iClient]);
            g_i1086Emitting[iClient] = -1;
        }
    }
}

Attribute_1086_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SOUND_WHILE_ACTIVE)) return iButtons;

    new bool:bFiring = IsWeaponFiring(iClient, iSlot);
    new bool:bForce = false;
    
    if (bFiring && GetEngineTime() >= g_f1086LastFire[iClient] + 2.0) bForce = true;
    
    if ((!bFiring || bForce) && g_i1086Emitting[iClient] == iSlot)
    {
        StopSound(iClient, SNDCHAN_WEAPON, g_str1086LastSound[iClient]);
        g_i1086Emitting[iClient] = -1;
    }
    if (bFiring && g_i1086Emitting[iClient] != iSlot)
    {
        new Handle:hArray = CreateArray(PLATFORM_MAX_PATH);
        for (new i = 0; i < sizeof(g_str1086Sounds); i++)
        {
            if (!StrEqual(g_str1086Sounds[i], g_str1086LastSound[iClient])) PushArrayString(hArray, g_str1086Sounds[i]);
        }
        if (GetArraySize(hArray) <= 0)
        {
            CloseHandle(hArray);
            return iButtons;
        }
        
        new iRandom = GetRandomInt(0, GetArraySize(hArray)-1);
        decl String:strPath[PLATFORM_MAX_PATH];
        GetArrayString(hArray, iRandom, strPath, sizeof(strPath));
        CloseHandle(hArray);
        
        EmitSoundToAll(strPath, iClient, SNDCHAN_WEAPON, _, SND_CHANGEVOL|SND_CHANGEPITCH, 1.0, GetRandomInt(60, 140));
        g_i1086Emitting[iClient] = iSlot;
        g_f1086LastFire[iClient] = GetEngineTime();
        
        strcopy(g_str1086LastSound[iClient], PLATFORM_MAX_PATH, strPath);
    }
    
    return iButtons;
}