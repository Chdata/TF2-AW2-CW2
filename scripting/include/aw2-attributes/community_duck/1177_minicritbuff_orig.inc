#define ATTRIBUTE_MINICRITS_AFTER_TAUNTING_2            1177

public Attribute_1177_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Taunting) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_MINICRITS_AFTER_TAUNTING_2)) return;

    new iSlot = GetClientSlot(iClient);
    
    new Float:fDuration = GetClientAttribute(iClient, iSlot, ATTRIBUTE_MINICRITS_AFTER_TAUNTING_2);
    
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MINICRITS_AFTER_TAUNTING_2)) return;
    
    TF2_AddCondition(iClient, TFCond_Buffed, fDuration);
}
    