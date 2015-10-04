#define ATTRIBUTE_HIGHER_JUMP      1167

Attribute_1167_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_HIGHER_JUMP))
    if (iButtons & IN_JUMP == IN_JUMP)
	if (OnGround(iClient))
	{
		new Float:fJumpVelocity[3];
		GetVelocity(iClient, fJumpVelocity);
		fJumpVelocity[2] = GetClientAttribute(iClient, iSlot, ATTRIBUTE_HIGHER_JUMP);
		TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, fJumpVelocity);
	}
    return iButtons;
}
