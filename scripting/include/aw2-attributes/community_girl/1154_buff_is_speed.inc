#define ATTRIBUTE_BUFF_IS_SPEED          1154

Attribute_1154_OnBuffedByBanner(iClient, iBuffer, iBuffType)
{
    if (!IsValidClient(iClient)) return;
    if (!IsValidClient(iBuffer)) return;
    if (!g_bBuffDeployer[iBuffer]) return;
    if (g_iBuffType[iBuffer] != 1) return;
    if (iBuffType == 0) return;
        
    // This checks if the person providing the buff has the attribute and then applies the buff
    
    PrintToChat(iClient, "BASIC BUFF SCRIPT WORKS");
    if (ClientHasAttribute(iBuffer, _, ATTRIBUTE_BUFF_IS_SPEED)) {
    TF2_AddCondition(iClient, TFCond_SpeedBuffAlly, 1.0);
    TF2_AddCondition(iBuffer, TFCond_SpeedBuffAlly, 1.0);
    }
}