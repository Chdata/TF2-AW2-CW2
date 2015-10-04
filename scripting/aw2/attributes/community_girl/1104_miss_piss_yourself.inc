#define ATTRIBUTE_MISS_PISS_YOURSELF      1104

new bool:g_bLastWasMiss1104[MAXPLAYERS+1] = false;

Attribute_1104_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MISS_PISS_YOURSELF))
    {
        g_bLastWasMiss1104[iClient] = false;
        CreateTimer(0.25, Attribute_1104_Expire, iClient);
    }
}

public Action:Attribute_1104_Expire(Handle:hTimer, any:iClient) 
{
    if (g_bLastWasMiss1104[iClient] == false)
        {
        TF2_AddCondition(iClient, TFCond_Jarated, 5.0);
        //This particle is friggin huge
        //AttachParticle(iClient, PARTICLE_POISON_GAS, 1.25);
        }
}

public Action:Attribute_1104_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_MISS_PISS_YOURSELF)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    g_bLastWasMiss1104[iAttacker] = true;
    
    return Plugin_Continue;
}
