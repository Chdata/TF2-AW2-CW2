#define ATTRIBUTE_GLIDE_PLAYER          1161

new Float:fAttribute_1161_Time[MAXPLAYERS+1] = 0.0;

Attribute_1161_Prethink(iClient, &iButtons, iSlot, &iButtonsLast)
{    
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_GLIDE_PLAYER)) return iButtons;
    if (OnGround(iClient))
    {
        fAttribute_1161_Time[iClient] = 0.0;
    }
    if (GetEntityMoveType(iClient) != MOVETYPE_WALK) return iButtons;
        
    decl Float:vVelocity[3];
    GetVelocity(iClient, vVelocity);
    
    fAttribute_1161_Time[iClient] += 0.1;
    
    new Float:fGlideTime = GetClientAttribute(iClient, iSlot, ATTRIBUTE_GLIDE_PLAYER);
    if (fAttribute_1161_Time[iClient] < fGlideTime)
    {
    new Float:fPush = -11.5;
    
    if (vVelocity[2] > 0)
    {
        vVelocity[2] -= fPush * 0.3;
    }
    else
    {
        vVelocity[2] += fPush * 1.0;
    }
    
    TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    }
    
    return iButtons;
}