#define ATTRIBUTE_ATTACK_WHILE_CLOAKED           1087

Attribute_1087_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ATTACK_WHILE_CLOAKED) && (iButtons & IN_ATTACK == IN_ATTACK))
    {
        new Float:flTime = GetGameTime();
        if (TF2_IsPlayerInCondition(iClient, TFCond_Cloaked))
        {
            TF2_RemoveCondition(iClient, TFCond_Cloaked);
            SetEntPropFloat(iClient, Prop_Send, "m_flNextAttack", flTime);
        }
        SetEntPropFloat(iClient, Prop_Send, "m_flStealthNoAttackExpire", flTime);
        SetEntPropFloat(iClient, Prop_Send, "m_flInvisChangeCompleteTime", flTime);
    }

    return iButtons;
}
