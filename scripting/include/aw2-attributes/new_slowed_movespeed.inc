#define ATTRIBUTE_NEW_SLOWED_MOVESPEED                  1005

Attribute_1005_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_NEW_SLOWED_MOVESPEED)) return iButtons;
    if (!TF2_IsPlayerInCondition(iClient, TFCond_Slowed)) return iButtons;
    
    new Float:fMaxSpeed = GetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed");
    if (fMaxSpeed <= 10.0) return iButtons;
    
    new Float:fSpeed = GetClientAttribute(iClient, iSlot, ATTRIBUTE_NEW_SLOWED_MOVESPEED) * 100.0;
    if (fMaxSpeed != fSpeed) {
        SetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed", fSpeed);
    }
    
    return iButtons;
}