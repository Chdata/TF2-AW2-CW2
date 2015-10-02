#define ATTRIBUTE_SOME_ALT_FIRE_DISABLED      1096

Attribute_1096_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SOME_ALT_FIRE_DISABLED))
	{
		if (iButtons & IN_ATTACK2 == IN_ATTACK2)
		{
			new weaponentity1096 = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
			SetEntPropFloat(weaponentity1096, Prop_Send, "m_flNextSecondaryAttack", GetGameTime()+999.0);
		}
	}
	return iButtons;
}
