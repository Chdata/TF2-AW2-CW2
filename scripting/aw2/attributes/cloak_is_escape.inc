#define ATTRIBUTE_CLOAK_IS_ESCAPE       1054
#define ATTRIBUTE_QUIET_UNSTEALTH       160

#define SOUND_ESCAPE_POOF               "AdvancedWeaponiser/poof.wav"

new g_iEscapeCloak[MAXPLAYERS+1] = 0;
new g_iEscapeCloakDamage[MAXPLAYERS+1] = 0;

Attribute_1054_Precache()
{
    SuperPrecacheSound(SOUND_ESCAPE_POOF);
}

Attribute_1054_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_CLOAK_IS_ESCAPE)) return iButtons;
    
    if (IsCloaked(iClient) && g_iEscapeCloak[iClient] <= 0)
    {
        RemoveStatusEffects(iClient);
        FastCloak(iClient);
        
        g_iEscapeCloak[iClient] = 0;
        g_iEscapeCloakDamage[iClient] = 0;
    }

    if (IsCloaked(iClient) != (g_iEscapeCloak[iClient] > 0))
    {
        new iHealth = GetClientHealth(iClient);
        if (iHealth > 0 && IsPlayerAlive(iClient))
        {
            if (!ClientHasAttribute(iClient, _, ATTRIBUTE_QUIET_UNSTEALTH))
			    {
                EmitSoundToAll(SOUND_ESCAPE_POOF, iClient);
                EmitSoundToAll(SOUND_ESCAPE_POOF, iClient);
                EmitSoundToClient(iClient, SOUND_ESCAPE_POOF);
				}
			else
				{
				EmitSoundToAll(SOUND_ESCAPE_POOF, iClient, _, _, SND_CHANGEVOL, SNDVOL_NORMAL*0.5);
				}

            decl Float:fOrigin[3];
            decl Float:fPos[3];
            new Float:fAng[3];
            
            GetClientAbsOrigin(iClient, fOrigin);
            fAng[0] = -90.0;
            
            fPos[0] = fOrigin[0];
            fPos[1] = fOrigin[1];
            fPos[2] = fOrigin[2] -30.0;
            ShowParticle(PARTICLE_EXPLOSION_FLASH, 2.0, fPos, fAng);
            for(new iLoop = 0; iLoop < 10; iLoop++) {
                fPos[0] = fOrigin[0] + GetRandomFloat(-8.0, 8.0);
                fPos[1] = fOrigin[1] + GetRandomFloat(-8.0, 8.0);
                fPos[2] = fOrigin[2] + GetRandomFloat(-5.0, 15.0);
                ShowParticle(PARTICLE_EXPLOSION_SMOKE, 2.0, fPos, fAng);
            }
        }
    }
    
    if (IsCloaked(iClient))
    {
        g_iEscapeCloak[iClient]++;
        SetEntPropFloat(iClient, Prop_Send, "m_flCloakMeter", 1.0);
        
        new iEscapeCloak = g_iEscapeCloak[iClient] - 30*3;
        if (iEscapeCloak < 0) iEscapeCloak = 0;
        new Float:fSpeed = GetEntPropFloat(iClient, Prop_Send, "m_flMaxspeed");
        if (fSpeed > 5.0) {
            new Float:fClassMaxSpeed = TF2_GetClassSpeed(GetPlayerClass(iClient));
            new Float:fNewMoveSpeed = 400.0 - float(iEscapeCloak) * 1.0;
            if (fNewMoveSpeed < fClassMaxSpeed) fNewMoveSpeed = fClassMaxSpeed;
            //TF2_AddCondition(iClient, TFCond_SpeedBuffAlly, 1.25);
            SetEntPropFloat(iClient, Prop_Send, "m_flMaxspeed", fNewMoveSpeed);
        }
        
        new Float:fDamage = float(iEscapeCloak)*0.05;
        new iDamageBoost = RoundFloat(fDamage);
        g_iEscapeCloakDamage[iClient] += iDamageBoost;
        if (g_iEscapeCloakDamage[iClient] >= 100)
        {
            g_iEscapeCloakDamage[iClient] = 0;
            new iHealth = GetClientHealth(iClient);
            if (iHealth > 1) SetEntityHealth(iClient, iHealth - 1);
            else DealDamage(iClient, 1);
        }
    }
    else
    {
        g_iEscapeCloak[iClient] = 0;
        g_iEscapeCloakDamage[iClient] = 0;
    }
    
    return iButtons;
}