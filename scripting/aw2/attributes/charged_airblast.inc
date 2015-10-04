#define ATTRIBUTE_CHARGED_AIRBLAST           165

new bool:g_bChargingAirblast[MAXPLAYERS+1] = false;

Attribute_165_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{    
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CHARGED_AIRBLAST) && (iButtons & IN_ATTACK2 == IN_ATTACK2))
    {
        if (!g_bChargingAirblast[iClient]) EmitSoundToClient(iClient, SOUND_CHARGE_STICKYBOMB, _, SNDCHAN_WEAPON);
        g_bChargingAirblast[iClient] = true;
    }
    else
    {
        if (g_bChargingAirblast[iClient]) StopSound(iClient, SNDCHAN_WEAPON, SOUND_CHARGE_STICKYBOMB);
        g_bChargingAirblast[iClient] = false;
    }
    
    return iButtons;
}