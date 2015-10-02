#define ATTRIBUTE_STICKYJUMP_DISABLE         1102

Attribute_1102_StickyJumpLand(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_STICKYJUMP_DISABLE)) return;
    if (!IsValidClient(iClient)) return;
    
    TF2_AddCondition(iClient, TFCond_Charging, 1.5);
    TF2_RemoveCondition(iClient, TFCond_Kritzkrieged);
}