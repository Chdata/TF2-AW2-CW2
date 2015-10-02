#define ATTRIBUTE_DISABLE_ENEMY_PRIMARY         1035

public Action:Attribute_1035_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (bBuilding) return Plugin_Continue;
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    if (IsAfterDamage(iDamageType)) return Plugin_Continue;
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_DISABLE_ENEMY_PRIMARY)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    if (DamageWillKill(iVictim, fDamage)) return Plugin_Continue;
    
    new Float:fTime = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_DISABLE_ENEMY_PRIMARY);
       
    if (MakeSlotSleep(iVictim, 0, fTime, true, SOUND_SAPPER_BREAK))
    {
        EmitSoundToAll(SOUND_SHIELD_BREAK, iVictim, SNDCHAN_WEAPON);
        EmitSoundToClient(iVictim, SOUND_SHIELD_BREAK);
        EmitSoundToClient(iAttacker, SOUND_SHIELD_BREAK);
    }
    
    return Plugin_Continue;
}