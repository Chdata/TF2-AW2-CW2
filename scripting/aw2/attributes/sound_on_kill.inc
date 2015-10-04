#define ATTRIBUTE_SOUND_ON_KILL         1094

new String:g_str1094Sounds[][PLATFORM_MAX_PATH] = {
    "slaggaming/goldengun.mp3"
};

Attribute_1094_Precache()
{    
    for (new i = 0; i < sizeof(g_str1094Sounds); i++)
    {
        SuperPrecacheSound(g_str1094Sounds[i]);
    }
}

Attribute_1094_OnDeath(iClient, &iAttacker, &iAssister, iSlot)
{
    if (!IsValidClient(iAttacker)) return;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_SOUND_ON_KILL)) return;
    if (iAttacker == iClient) return;
    
    new iValue = RoundFloat(GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_SOUND_ON_KILL));
    
    //PrintToChat(iAttacker, "A value: %d", iValue);
    
    if (iValue > sizeof(g_str1094Sounds)) return;
    if (iValue < 0) return;
    
    new iRandom = GetRandomInt(0, sizeof(g_str1094Sounds)-1);
    
    EmitSoundToAll(g_str1094Sounds[iRandom], iAttacker, SNDCHAN_WEAPON);
    
    //PrintToChat(iAttacker, "B Playing sound: %s", g_str1094Sounds[iRandom]);
    
    return;
}
