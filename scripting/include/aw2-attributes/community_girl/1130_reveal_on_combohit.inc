#define ATTRIBUTE_REVEAL_ON_HIT            1130

#define BONUSDMG_1130_A                0.75
#define BONUSDMG_1130_B                1.00
#define BONUSDMG_1130_C                1.25

new g_iRevealCombo1130[MAXPLAYERS+1] = 0;
new bool:g_iRevealComboHit1130[MAXPLAYERS+1] = false;

Attribute_1130_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_REVEAL_ON_HIT)) return;
    g_iRevealCombo1130[iClient] = 0;
}

Attribute_1130_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_REVEAL_ON_HIT)) return;
    if (g_iRevealCombo1130[iClient] > 0) 
	{
        g_iRevealComboHit1130[iClient] = false;
        CreateTimer(0.1, Attribute_1130_Expire, iClient);
    }
}
public Action:Attribute_1130_Expire(Handle:hTimer, any:iClient) {
    if (!g_iRevealComboHit1130[iClient]) 
    {
        g_iRevealCombo1130[iClient] = 0;
    }
}
public Action:Attribute_1130_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
if (!IsValidClient(iAttacker)) return Plugin_Continue;
if (iAttacker == iVictim) return Plugin_Continue;
if (bBuilding) return Plugin_Continue;

if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_REVEAL_ON_HIT)) return Plugin_Continue;
if (fDamage <= 0.0) return Plugin_Continue;

g_iRevealComboHit1130[iAttacker] = true;
g_iRevealCombo1130[iAttacker]++;
    
if (g_iRevealCombo1130[iAttacker] <= 1) 
{
fDamage *= BONUSDMG_1130_A;
}
else if (g_iRevealCombo1130[iAttacker] == 2) 
{
fDamage *= BONUSDMG_1130_B;
}
else if (g_iRevealCombo1130[iAttacker] >= 3)
{		
TF2_AddCondition(iVictim, TFCond_Unknown2, GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_REVEAL_ON_HIT));
fDamage *= BONUSDMG_1130_C;
g_iRevealCombo1130[iAttacker] = 0;
EmitSoundToAll(SOUND_MARKED_REV, iVictim);
AttachParticle(iVictim, PARTICLE_STARRY_BURST, 1.25);
}
return Plugin_Changed;
}

public Attribute_1130_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Unknown2) return;
    SetEntProp(iClient, Prop_Send, "m_bGlowEnabled", 1, 1);
}
public Attribute_1130_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Unknown2) return;
    SetEntProp(iClient, Prop_Send, "m_bGlowEnabled", 0, 0);
}
