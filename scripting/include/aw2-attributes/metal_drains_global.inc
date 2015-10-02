#define ATTRIBUTE_METAL_DRAINS_GLOBAL         1077

new g_i177MetalDrain[MAXPLAYERS+1] = 0;

Attribute_1077_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_METAL_DRAINS_GLOBAL)) return iButtons;
    g_i177MetalDrain[iClient] += 1;
    
    if (g_i177MetalDrain[iClient] >= 60)
    {
        new Float:fMetal = GetClientAttribute(iClient, iSlot, ATTRIBUTE_METAL_DRAINS_GLOBAL);
        fMetal = FloatAbs(fMetal)*-1.0;
        new iMetal = RoundFloat(fMetal);
        GiveEngineerMetal(iClient, iMetal);
        g_i177MetalDrain[iClient] = 0;
    }
    
    return iButtons;
}