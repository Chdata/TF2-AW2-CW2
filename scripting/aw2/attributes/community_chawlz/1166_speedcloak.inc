#define ATTRIBUTE_SPEED_WHILE_CLOAKED           1166

Attribute_1166_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {

    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_SPEED_WHILE_CLOAKED)) return iButtons;
    if (!IsCloaked(iClient)) return iButtons;

    
//    new Float:fMaxSpeed = GetEntPropFloat(iClient, Prop_Send, "m_flMaxspeed");
//    new Float:fSpeed = GetClientAttribute(iClient, _, ATTRIBUTE_SPEED_WHILE_CLOAKED) * 100.0;
//
//    if (IsCloaked(iClient))
//        {
//        SetEntPropFloat(iClient, Prop_Send, "m_flMaxSpeed", fSpeed);
//        }
    

    //new Float:fMaxSpeed = GetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed");
    new Float:fClassSpeed = TF2_GetClassSpeed(GetPlayerClass(iClient));
    //if (fMaxSpeed <= 10.0) return iButtons;
    
    new Float:fSpeed = fClassSpeed * GetClientAttribute(iClient, iSlot, ATTRIBUTE_SPEED_WHILE_CLOAKED);
    //if (fMaxSpeed != fSpeed) {
    SetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed", fSpeed);
    //}
    
    return iButtons;
}