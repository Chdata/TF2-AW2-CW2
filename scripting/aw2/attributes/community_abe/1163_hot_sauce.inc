// If only the train whistle was from Rhythm Heaven Fever Munchy Monk mini-game...
// The sound file is a placeholder for now, until we can get an actual train whistle sound.
// Lots of redundancy for losing the fire condition. Maybe it's a bit overboard.

#define ATTRIBUTE_DRINK_IS_HOT_SAUCE         1163
#define SOUND_CHOO_CHOO                        "ambient/train.wav"

new bool:g_bIsCharging1163[MAXPLAYERS+1] = false;

Attribute_1163_Precache()
{
    SuperPrecacheSound(SOUND_CHOO_CHOO);
}

public Attribute_1163_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Bonked) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_DRINK_IS_HOT_SAUCE)) return;

    TF2_RemoveCondition(iClient, TFCond_Bonked);
    TF2_AddCondition(iClient, TFCond_OnFire, 10.0);
    TF2_AddCondition(iClient, TFCond_Charging, 10.0);
    TF2_RemoveCondition(iClient, TFCond_Kritzkrieged);
    SetEntPropFloat(iClient, Prop_Send, "m_flMaxSpeed", 750.0);

    g_bIsCharging1163[iClient] = true;
    CreateTimer(10.0, Attribute_1163_Expire, iClient);
    CreateTimer(5.5, Attribute_1163_Sound, iClient);
    CreateTimer(1.0, Attribute_1163_Sound, iClient);
}

Attribute_1163_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, _, ATTRIBUTE_DRINK_IS_HOT_SAUCE) && g_bIsCharging1163[iClient])
    {
    SetEntPropFloat(iClient, Prop_Send, "m_flMaxSpeed", 750.0);
    TF2_RemoveCondition(iClient, TFCond_Kritzkrieged);
    TF2_IgnitePlayer(iClient, iClient);
    }
    
    return iButtons;
}

Attribute_1163_OnExtinguished(iVictim, iHealer)
{
    if (!IsValidClient(iVictim)) return;
    if (!IsValidClient(iHealer)) return;
    if (!ClientHasAttribute(iVictim, _, ATTRIBUTE_DRINK_IS_HOT_SAUCE)) return;
    
    if (g_bIsCharging1163[iVictim])
    {
    TF2_AddCondition(iVictim, TFCond_OnFire, 10.0);
    }
}

public Attribute_1163_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_DRINK_IS_HOT_SAUCE)) return;
        
    if (condition == TFCond_Charging) {
    if (!g_bIsCharging1163[iClient]) {
    TF2_RemoveCondition(iClient, TFCond_OnFire);
    g_bIsCharging1163[iClient] = false;
    }
    if (g_bIsCharging1163[iClient]) {
    TF2_AddCondition(iClient, TFCond_Charging, 10.0);
    }
    
    }
    if (condition == TFCond_OnFire) {
    if (g_bIsCharging1163[iClient]) {
    TF2_AddCondition(iClient, TFCond_OnFire, 10.0);
    }
    }
}
    
public Action:Attribute_1163_Expire(Handle:hTimer, any:iClient)
{
    g_bIsCharging1163[iClient] = false;
    SetEntPropFloat(iClient, Prop_Send, "m_flMaxSpeed", 450.0);
}

public Action:Attribute_1163_Sound(Handle:hTimer, any:iClient)
{
    if (!IsValidClient(iClient)) return;

    EmitSoundToAll(SOUND_CHOO_CHOO, iClient, _, SNDLEVEL_SCREAMING);
} 
