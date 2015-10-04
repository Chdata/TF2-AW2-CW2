#define ATTRIBUTE_SPY_ONFIRE            1125

public Attribute_1125_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_OnFire) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_SPY_ONFIRE)) return;
    TF2_AddCondition(iClient, TFCond_SpeedBuffAlly, 2.5);
}
public Attribute_1125_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_OnFire) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_SPY_ONFIRE)) return;
    TF2_RemoveCondition(iClient, TFCond_SpeedBuffAlly);
}