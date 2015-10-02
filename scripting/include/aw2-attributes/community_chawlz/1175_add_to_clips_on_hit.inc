#define ATTRIBUTE_ADD_CLIPS_ON_HIT		1175

public Action:Attribute_1175_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (bBuilding) return Plugin_Continue;
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_ADD_CLIPS_ON_HIT)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	
	new iPrimaryWeapon = GetPlayerWeaponSlot(iAttacker, 0);
	new iSecondaryWeapon = GetPlayerWeaponSlot(iAttacker, 1);
	
	new Float:fPrimarySize = 4.0;
	new Float:fSecondarySize = 8.0;	
	
	decl String:strPrimaryName[PLATFORM_MAX_PATH];
	GetEdictClassname(iPrimaryWeapon, strPrimaryName, sizeof(strPrimaryName));
	
	decl String:strSecondaryName[PLATFORM_MAX_PATH];
	GetEdictClassname(iSecondaryWeapon, strSecondaryName, sizeof(strSecondaryName));

	if (!StrEqual(strPrimaryName, "tf_wearable"))
	{
		new iPrimaryClip = GetEntProp(iPrimaryWeapon, Prop_Send, "m_iClip1");
		PrintToChat(iAttacker, "Beofre hit primary: %i", iPrimaryClip);
		
		if (StrEqual(strPrimaryName, "tf_weapon_shotgun_primary")) fPrimarySize = 6.0;
		
		if (ClientHasAttribute(iAttacker, iPrimaryWeapon, 3)) fPrimarySize *= GetClientAttribute(iAttacker, iPrimaryWeapon, 3);
		if (ClientHasAttribute(iAttacker, iPrimaryWeapon, 4)) fPrimarySize *= GetClientAttribute(iAttacker, iPrimaryWeapon, 4);
		
		if (iPrimaryClip << RoundFloat(fPrimarySize))
		{
			//SHOULD only add to player's primary clip if the primary item is a valid weapon AND isn't already full. Keyword is "should".
			iPrimaryClip += 1;
			SetEntProp(iPrimaryWeapon, Prop_Send, "m_iClip1", iPrimaryClip);
			PrintToChat(iAttacker, "After hit primary: %i", iPrimaryClip);
			//SetEntData(iPrimaryWeapon,FindSendPropOffs("CBaseCombatWeapon", "m_iClip1"),iAmmo2,4);
		}
	}
	else PrintToChat(iAttacker, "Nope, your wearin boots");
	
	if (!StrEqual(strSecondaryName, "tf_wearable_demoshield"))
	{
		new iSecondaryClip = GetEntProp(iAttacker, Prop_Send, "m_iClip1");
		PrintToChat(iAttacker, "Before hit secondary: %i", iSecondaryClip);
		
		if (ClientHasAttribute(iAttacker, iSecondaryWeapon, 3)) fPrimarySize *= GetClientAttribute(iAttacker, iSecondaryWeapon, 3);
		if (ClientHasAttribute(iAttacker, iSecondaryWeapon, 4)) fPrimarySize *= GetClientAttribute(iAttacker, iSecondaryWeapon, 4);

		if (iSecondaryClip << RoundFloat(fSecondarySize))
		{
			iSecondaryClip += 1;
			SetEntProp(iSecondaryWeapon, Prop_Send, "m_iClip1", iSecondaryClip);
			PrintToChat(iAttacker, "After hit secondary: %i", iSecondaryClip);
			//SetEntData(iSecondaryWeapon,FindSendPropOffs("CBaseCombatWeapon", "m_iClip1"),fSecondaryClip,4);
		}
	}
	else PrintToChat(iAttacker, "Nope, youve got a shield");
	
	return Plugin_Continue;
}
