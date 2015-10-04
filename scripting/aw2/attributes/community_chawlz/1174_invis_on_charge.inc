#define ATTRIBUTE_INVIS_ON_CHARGE         1174

Attribute_1174_Precache()
{
    SuperPrecacheSound(SOUND_1174_CHARGEPOOF);
}

public Attribute_1174_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_INVIS_ON_CHARGE)) return;
    if (condition != TFCond_Charging) return;

    HideClientWearables(iClient, true);
    HideEntity(iClient, true);

    EmitSoundToAll(SOUND_1174_CHARGEPOOF, iClient);
    EmitSoundToClient(iClient, SOUND_1174_CHARGEPOOF);
    
    return;
}


public Attribute_1174_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_INVIS_ON_CHARGE)) return;
    if (condition != TFCond_Charging) return;
   
    HideClientWearables(iClient, false);
    HideEntity(iClient, false);
    
    return;
}