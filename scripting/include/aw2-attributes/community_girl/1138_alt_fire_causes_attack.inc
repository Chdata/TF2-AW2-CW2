#define ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK      1138

new g_bIsAltFire1138[MAXPLAYERS+1] = 0;
new bool:g_bAltFireMissed1138[MAXPLAYERS+1] = false;
new Float:g_f1138Heal[MAXPLAYERS+1] = 0.0;

//This is the main thingy which causes alt-fire

Attribute_1138_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK) && (iButtons & IN_ATTACK2 == IN_ATTACK2))
    {
    iButtons |= IN_ATTACK;
    g_bIsAltFire1138[iClient] = 0;
    g_bAltFireMissed1138[iClient] = false;
    }
    else
    {
    g_bIsAltFire1138[iClient] = 1;
    g_bAltFireMissed1138[iClient] = false;
    }
    return iButtons;
}

//This is for configuring effects that always occur when you fire the weapon

Attribute_1138_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK)) return;
    if (g_bIsAltFire1138[iClient] == 0)
	{
        g_bAltFireMissed1138[iClient] = false;
        CreateTimer(0.1, Attribute_1138_Expire_Miss, iClient);
        
        new Float:Cond = GetClientAttribute(iClient, iSlot, ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK);
        
        if (Cond == 8.0)
        {
        new iAmmoClip = GetWeaponAmmo(iClient, 1, false);
        if (iAmmoClip <= 1) return;
        iAmmoClip -= 2;       
        SetWeaponAmmo(iClient, 1, 0, iAmmoClip);
        }
        else if (Cond == 9.0)
        {
        new iAmmoClip = GetWeaponAmmo(iClient, 1, false);
        if (iAmmoClip <= 2) return;
        iAmmoClip -= 3;       
        SetWeaponAmmo(iClient, 1, 0, iAmmoClip);
        }
        else if (Cond == 10.0)
        {
            TF2_AddCondition(iClient, TFCond_Bleeding, 2.0);
        }
    }
}

// This is for configuring on-hit effects

public Action:Attribute_1138_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK)) return Plugin_Continue;
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    if (g_bIsAltFire1138[iAttacker] == 1) return Plugin_Continue;

    new Float:Cond = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK);
    
    if (Cond <= 1.0)
    {
    fDamage *= 0.50;
    NormalizeVector(fForce, fForce);
    if (fForce[2] < 0.2) fForce[2] = 0.2;
    
    new Float:fScale1138 = fDamage*18.5;
    if (fScale1138 < 100.0) fScale1138 = 100.0;
    if (fScale1138 > 600.0) fScale1138 = 600.0;
    ScaleVector(fForce, fScale1138);
    if (fForce[2] < 320.0 && fDamage >= 10.0) fForce[2] = 320.0;
    
    decl Float:vClientVelocity[3];
    GetVelocity(iVictim, vClientVelocity);
    AddVectors(vClientVelocity, fForce, vClientVelocity);
    TeleportEntity(iVictim, NULL_VECTOR, NULL_VECTOR, vClientVelocity);
    }
    else if (Cond == 2.0)
    {
        TF2_AddCondition(iVictim, TFCond_Jarated, 2.5);
        fDamage *= 0.8;
    }
    else if (Cond == 3.0)
    {
        TF2_AddCondition(iVictim, TFCond_Milked, 3.0);
        fDamage *= 0.70;
    }
    else if (Cond == 4.0)
    {
        TF2_AddCondition(iVictim, TFCond_Bleeding, 5.0);
        fDamage *= 0.40;
    }
    else if (Cond == 5.0)
    {
        new Float:fHealed = 2.0;
        fDamage *= 0.50;
        g_f1138Heal[iAttacker] += fHealed;
        if (g_f1138Heal[iAttacker] >= 1.0)
        {
        new iHeal = RoundToFloor(g_f1138Heal[iAttacker]);
        if (iHeal >= 1)
            {
                g_f1138Heal[iAttacker] -= float(iHeal);
                new iHealth = GetClientHealth(iAttacker);
                iHealth += iHeal;
                new iOverHeal = GetClientMaxOverHeal(iAttacker);
                if (iHealth > iOverHeal) iHealth = iOverHeal;
                SetEntityHealth(iAttacker, iHealth);
            }
    }
    }
    else if (Cond == 6.0)
    {
        TF2_IgnitePlayer(iVictim, iAttacker);
        fDamage *= 0.35;
    }
    else if (Cond == 7.0)
    {
        TF2_AddCondition(iVictim, TFCond_MarkedForDeath, 5.0);
        fDamage *= 0.40;
    }
    else if (Cond == 8.0)
    {
        new iCheck = GetEntData(iAttacker, FindSendPropOffs("CTFPlayer", "m_iAmmo")+4);
        
        if (iCheck > 1)
        {
        ApplyMinicrit(iVictim, iAttacker);
        iDamageType = RemoveCritDamageType(iDamageType);
        fDamage *= 1.35;
        }
    }
    else if (Cond == 9.0)
    {
        new iCheck = GetEntData(iAttacker, FindSendPropOffs("CTFPlayer", "m_iAmmo")+4);
        
        if (iCheck > 2)
        {
        iDamageType = MakeCritDamageType(iDamageType);
        }
    }
    else if (Cond == 10.0)
    {
        fDamage *= 1.20;
    }
    else if (Cond == 11.0)
    {
        fDamage *= 1.30;
    }
    
    g_bAltFireMissed1138[iAttacker] = true;
    g_bIsAltFire1138[iAttacker] = 1;
    
    return Plugin_Changed;
}

public Action:Attribute_1138_Expire_Miss(Handle:hTimer, any:iClient) 
{
    if (g_bAltFireMissed1138[iClient] == false)
	{   
    new Float:Cond = GetClientAttribute(iClient, _, ATTRIBUTE_ALT_FIRE_CAUSES_ATTACK);    
    if (Cond == 11.0)
    {
    TF2_AddCondition(iClient, TFCond_Milked, 5.0);
    }
    }
}