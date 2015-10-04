#define ATTRIBUTE_FASTER_BUILDING_CARRY		1150

Attribute_1150_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FASTER_BUILDING_CARRY)) return iButtons;
	new bCarry = GetEntProp(iClient, Prop_Data, "m_bCarryingObject");
	new Float:fMaxSpeed = GetEntPropFloat(iClient, Prop_Data, "m_flMaxspeed");
	//Zero is false
	if (bCarry == 0) return iButtons;
	if (fMaxSpeed <= 10.0) return iButtons;

	//225v is HU speed of Engie carrying building
	new Float:fSpeed = GetClientAttribute(iClient, _, ATTRIBUTE_FASTER_BUILDING_CARRY) * 225.0;
	SetEntPropFloat(iClient, Prop_Data, "m_flMaxSpeed", fSpeed);
	return iButtons;
}
