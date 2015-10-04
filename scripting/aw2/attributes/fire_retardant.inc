#define ATTRIBUTE_FIRE_RETARDANT        1000

public Action:Attribute_1000_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iVictim)) return Plugin_Continue;
    if (!ClientHasAttribute(iVictim, _, ATTRIBUTE_FIRE_RETARDANT)) return Plugin_Continue;
    
    if (IsDamageTypeFire(iDamageType))
    {    
        new Float:fMulti = GetClientAttribute(iVictim, _, ATTRIBUTE_FIRE_RETARDANT);
        fDamage *= fMulti;
        
        DealDamage(iVictim, RoundFloat(fDamage), iAttacker, _, "flamethrower");
        
        /*
        new bool:bCrit = IsDamageTypeCrit(iDamageType);
        DealDamage(iVictim, RoundFloat(fDamage), iAttacker, TF_WEAPON_FLAMETHROWER, bCrit);
        */
        
        fDamage = 0.0;
        return Plugin_Changed;
    }
    
    return Plugin_Changed;
}