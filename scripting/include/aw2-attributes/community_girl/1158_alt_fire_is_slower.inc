#define ATTRIBUTE_ALT_FIRE_IS_SLOWER        1158

Attribute_1158_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ALT_FIRE_IS_SLOWER))
	{        
        if (iButtons & IN_ATTACK2 == IN_ATTACK2)
		{
        new Float:RateofFire = GetClientHealth(iClient)*0.0005;
        new weaponentity = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
        SetEntPropFloat(weaponentity, Prop_Send, "m_flNextPrimaryAttack", GetGameTime()-RateofFire);
		}
	}
	return iButtons;
}