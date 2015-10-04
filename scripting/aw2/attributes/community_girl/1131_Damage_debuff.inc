#define ATTRIBUTE_TEST_BUBBLES      1131

Attribute_1131_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_TEST_BUBBLES))
	{
		if (iButtons & IN_ATTACK == IN_ATTACK)
		{
        SetEntProp(iClient, Prop_Data, "m_bPlayerUnderwater", 1);
        SetEntProp(iClient, Prop_Data, "m_nDrownDmgRate", 0);
        SetEntProp(iClient, Prop_Data, "m_idrowndmg", 0);
        SetEntPropFloat(iClient, Prop_Send, "m_flFriction", 0.0);
        SetEntProp(iClient, Prop_Data, "m_nWaterLevel", 4);
        }
	}
	return iButtons;
}
