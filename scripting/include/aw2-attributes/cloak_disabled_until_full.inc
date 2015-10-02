#define ATTRIBUTE_CLOAK_DISABLED_UNTIL_FULL         1071

Attribute_1071_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CLOAK_DISABLED_UNTIL_FULL)) return iButtons;
    if (IsCloaked(iClient)) return iButtons;
    
    new Float:fCloak = GetEntPropFloat(iClient, Prop_Send, "m_flCloakMeter");
    
    if (fCloak < 100.0 && iButtons & IN_ATTACK2 == IN_ATTACK2)
    {
        iButtons &= ~IN_ATTACK2;
    }
    
    return iButtons;
}