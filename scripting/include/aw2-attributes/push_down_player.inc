#define ATTRIBUTE_PUSH_DOWN_PLAYER          1034

new Float:fAttribute_1034_Time[MAXPLAYERS+1] = 0.0;

Attribute_1034_Prethink(iClient, &iButtons, iSlot, &iButtonsLast)
{    
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_PUSH_DOWN_PLAYER)) return iButtons;
    //PrintToChat(iClient, "YES! YES! YES!");
    if (OnGround(iClient))
    {
        fAttribute_1034_Time[iClient] = 0.0;
    }
    if (GetEntityMoveType(iClient) != MOVETYPE_WALK) return iButtons;
    
    //PrintToChat(iClient, "heavy2");
    
    decl Float:vVelocity[3];
    GetVelocity(iClient, vVelocity);
    
    fAttribute_1034_Time[iClient] += 0.1;
    if (fAttribute_1034_Time[iClient] > 1.0) fAttribute_1034_Time[iClient] = 1.0;
    
    new Float:fPush = GetClientAttribute(iClient, iSlot, ATTRIBUTE_PUSH_DOWN_PLAYER) * fAttribute_1034_Time[iClient];
    
    if (vVelocity[2] > 0)
    {
        vVelocity[2] -= fPush * 0.3;
    }
    else
    {
        vVelocity[2] -= fPush * 1.0;
    }
    
    TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    
    return iButtons;
}