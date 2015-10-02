#define ATTRIBUTE_LOSE_CHARGE_ON_FULL		  1199

#define SOUND_1199_LOSE_CHARGE		  "items/suitchargeno1.wav"

Attribute_1199_Precache()
{
	SuperPrecacheSound(SOUND_1199_LOSE_CHARGE);
}

Attribute_1199_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast) {
	if (!ClientHasAttribute(iClient, _, ATTRIBUTE_LOSE_CHARGE_ON_FULL)) return iButtons;
	if (!TF2_IsPlayerInCondition(iClient, TFCond_Zoomed)) return iButtons;

	new iWeapon = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
	new Float:fCharge = GetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage");

	if (fCharge >= 149.0)
		{
		//TF2_RemoveCondition(iClient, TFCond_Zoomed);
		//TF2_RemoveCondition(iClient, TFCond_Slowed);
		iButtons = IN_ATTACK2;
		EmitSoundToClient(iClient, SOUND_1199_LOSE_CHARGE);
		SetEntPropFloat(iWeapon, Prop_Send, "m_flChargedDamage", 0.0);
		} 
	return iButtons;
}