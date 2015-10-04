#define ATTRIBUTE_ON_HIT_GABEN	  1201

#define SOUND_1201_GABEN	"commentary/tf2-comment000.wav"

Attribute_1201_Precache()
{
	SuperPrecacheSound(SOUND_1201_GABEN);
}

public Action:Attribute_1201_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
	if (!IsValidClient(iAttacker)) return Plugin_Continue;	
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_ON_HIT_GABEN)) return Plugin_Continue;
	if (fDamage <= 0.0) return Plugin_Continue;
	
	TF2_StunPlayer(iVictim, 4.0, 0.0, TF_STUNFLAG_THIRDPERSON|TF_STUNFLAG_NOSOUNDOREFFECT|TF_STUNFLAG_BONKSTUCK);
	TF2_StunPlayer(iAttacker, 4.5, 0.0, TF_STUNFLAG_THIRDPERSON|TF_STUNFLAG_NOSOUNDOREFFECT|TF_STUNFLAG_BONKSTUCK);
	EmitSoundToAll(SOUND_1201_GABEN, iVictim, _, _, SND_CHANGEVOL, SNDVOL_NORMAL*1.5);
	
	return Plugin_Continue;
}
