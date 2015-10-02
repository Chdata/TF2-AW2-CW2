#define ATTRIBUTE_FREELY_DEPLOY_UBERCHARGE      1006

Attribute_1006_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FREELY_DEPLOY_UBERCHARGE))
    {
        new Float:fDeployLimit = GetClientAttribute(iClient, iSlot, ATTRIBUTE_FREELY_DEPLOY_UBERCHARGE) * 100.0;
        new Float:fUberCharge = TF2_GetPlayerUberLevel(iClient);
        if ((iButtons & IN_ATTACK2 == IN_ATTACK2) && fUberCharge > fDeployLimit)
        {
            if (fUberCharge <= 90.0)
            {
                new iTarget = GetHealTarget(iClient);
                if (IsValidClient(iTarget))
                {
                    if (IsPlayerAlive(iTarget))
                    {
                        new iTargetHealth = GetClientHealth(iTarget);
                        new iTargetMaxHealth = GetClientMaxHealth(iTarget);
                        if (iTargetHealth/iTargetMaxHealth <= 0.20)
                        {
                            SlagInv_AddAchievementProgress(iClient, "aw2_malpractice");
                        }
                    }
                }
            }
            ReleaseUbercharge(iClient);
        }
        if (IsUberchargeDeployed(iClient) && TF2_IsPlayerInCondition(iClient, TFCond_Ubercharged))
        {
            TF2_RemoveCondition(iClient, TFCond_Ubercharged);
        }
    }
    
    return iButtons;
}
