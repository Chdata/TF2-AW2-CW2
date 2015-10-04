#define ATTRIBUTE_CLOAK_REGEN_RATE_CUSTOM         1070

Attribute_1070_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CLOAK_REGEN_RATE_CUSTOM)) return iButtons;
    if (IsCloaked(iClient)) return iButtons;

    new Float:fValue = GetClientAttribute(iClient, iSlot, ATTRIBUTE_CLOAK_REGEN_RATE_CUSTOM) - 1.0;
    ModifyCloak(iClient, fValue*0.08);
    
    return iButtons;
}