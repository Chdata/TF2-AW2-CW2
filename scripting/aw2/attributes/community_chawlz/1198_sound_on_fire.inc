#define ATTRIBUTE_SOUND_ON_FIRE	 1198

//Plays a sound when the weapon is fired, where the attribute's value is the sound ID played. Feel free to add sounds!

#define SOUND_ONFIRE_1				   "advancedweaponiser/boilerbuss_shoot.wav"
#define SOUND_ONFIRE_2				   "advancedweaponiser/nail_gun_shoot.wav"
#define SOUND_ONFIRE_3				   "advancedweaponiser/ragelauncher_shoot.wav"

#define SOUND_ONFIRE_1_ABE			   "weapons/pomson_fire_01.wav"

#define SOUND_ONFIRE_CRIT				"advancedweaponiser/crit_generic.wav"

new String:g_strAprFoolHacks[][PLATFORM_MAX_PATH] = {
	"vo/npc/male01/hacks01.wav",
	"vo/npc/male01/hacks02.wav"
};

Attribute_1198_Precache()
{
	SuperPrecacheSound(SOUND_ONFIRE_1);
	SuperPrecacheSound(SOUND_ONFIRE_2);
	SuperPrecacheSound(SOUND_ONFIRE_3);
	
	SuperPrecacheSound(SOUND_ONFIRE_1_ABE);

	SuperPrecacheSound(SOUND_ONFIRE_CRIT);

	for (new i = 0; i < sizeof(g_strAprFoolHacks); i++)
	{
		SuperPrecacheSound(g_strAprFoolHacks[i]);
	}
}

Attribute_1198_OnAttack(iClient, iSlot, &bool:bCrit)
{
	if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_SOUND_ON_FIRE)) return;

	new iSound = RoundFloat(GetClientAttribute(iClient, iSlot, ATTRIBUTE_SOUND_ON_FIRE));

	switch (iSound)
	{
		case 1:
		{
			EmitSoundToAll(SOUND_ONFIRE_1, iClient);
		}

		case 2:
		{
			EmitSoundToAll(SOUND_ONFIRE_2, iClient);
		}

		case 3:
		{
			//Potential Rage Launcher sound, gets deeper as rage goes up.
			new Float:fRage = GetEntPropFloat(iClient, Prop_Send, "m_flRageMeter");
			new iPitch = RoundFloat(100-(fRage/2));
			EmitSoundToAll(SOUND_ONFIRE_3, iClient, _, SNDLEVEL_SCREAMING, SND_CHANGEPITCH, SNDVOL_NORMAL, iPitch);
		}
		case 1001:
		{
			EmitSoundToAll(SOUND_ONFIRE_1_ABE, iClient);
		}
	}

	if (bCrit) EmitSoundToAll(SOUND_ONFIRE_CRIT, iClient);
}

public Action:Attribute_1198_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (bBuilding) return Plugin_Continue;
	if (!IsValidClient(iAttacker)) return Plugin_Continue;
	if (iAttacker == iVictim) return Plugin_Continue;
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_SOUND_ON_FIRE)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;

	if ((GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_SOUND_ON_FIRE) == 4.0) && (iDamageType & TF_DMG_RIFLE_CRIT == TF_DMG_RIFLE_CRIT))
	{
		new iRandom = GetRandomInt(0, sizeof(g_strAprFoolHacks)-1);
		EmitSoundToAll(g_strAprFoolHacks[iRandom], iVictim, _, SNDLEVEL_GUNFIRE);
		EmitSoundToClient(iAttacker, g_strAprFoolHacks[iRandom]);
	}

	return Plugin_Continue;
}