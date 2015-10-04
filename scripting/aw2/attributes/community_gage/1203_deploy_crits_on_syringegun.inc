#define ATTRIBUTE_DEPLOY_CRITS_ON_SYRINGEGUN      1203

Attribute_1203_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_DEPLOY_CRITS_ON_SYRINGEGUN))
    {
        new Float:fDeployLimit = GetClientAttribute(iClient, iSlot, ATTRIBUTE_DEPLOY_CRITS_ON_SYRINGEGUN) * 100.0;
        new Float:fUberCharge = TF2_GetPlayerUberLevel(iClient);
        if ((iButtons & IN_ATTACK2 == IN_ATTACK2) && fUberCharge >= fDeployLimit)
        {
            TF2_AddCondition(iClient, TFCond_Kritzkrieged, 4.50);
            new Float:fUber = TF2_GetPlayerUberLevel(iClient);
            fUber -= fDeployLimit;
            TF2_SetPlayerUberLevel(iClient, fUber);
        }
    }
    
    return iButtons;
}

//My first code ^^ (Duck helped me with it)