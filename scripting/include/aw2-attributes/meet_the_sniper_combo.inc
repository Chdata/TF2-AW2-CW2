//Decided to nerf the Walkabout slightly, it now deals far less damage during the initial combo-increase. This should incentivize switching to another weapon or gambling on the three hit combo in close range, instead of retaining most of your no-scope damage.

#define ATTRIBUTE_MEET_THE_SNIPER_COMBO         1016

#define SOUND_1016_A                        "physics/surfaces/underwater_impact_bullet1.wav"
#define SOUND_1016_B                        "physics/surfaces/underwater_impact_bullet2.wav"
#define SOUND_1016_C                        "physics/surfaces/underwater_impact_bullet3.wav"

#define SNIPER_COMBO_1016_1A                "AdvancedWeaponiser/walkabout_combo_1a.wav"
#define SNIPER_COMBO_1016_1B                "AdvancedWeaponiser/walkabout_combo_1b.wav"
#define SNIPER_COMBO_1016_2                 "AdvancedWeaponiser/walkabout_combo_2.wav"
#define SNIPER_COMBO_1016_3                 "AdvancedWeaponiser/walkabout_combo_3.wav"

#define DMGBONUS_1016_A                0.35
#define DMGBONUS_1016_B                0.60
#define DMGBONUS_1016_C                3.00

new g_iSniperCombo1016[MAXPLAYERS+1] = 0;
new bool:g_iSniperComboHit1016[MAXPLAYERS+1] = false;

Attribute_1016_Precache()
{
    SuperPrecacheSound(SNIPER_COMBO_1016_1A);
    SuperPrecacheSound(SNIPER_COMBO_1016_1B);
    SuperPrecacheSound(SNIPER_COMBO_1016_2);
    SuperPrecacheSound(SNIPER_COMBO_1016_3);
}

Attribute_1016_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEET_THE_SNIPER_COMBO)) return;
    g_iSniperCombo1016[iClient] = 0;
}

Attribute_1016_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEET_THE_SNIPER_COMBO)) return;
    
    if (g_iSniperCombo1016[iClient] > 0) {
        g_iSniperComboHit1016[iClient] = false;
        CreateTimer(0.1, Attribute_1016_Expire, iClient);
    }
}

public Action:Attribute_1016_Expire(Handle:hTimer, any:iClient) {
    if (!g_iSniperComboHit1016[iClient]) {
        g_iSniperCombo1016[iClient] = 0;
    }
}

public Action:Attribute_1016_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;
    if (iAttacker == iVictim) return Plugin_Continue;
    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_MEET_THE_SNIPER_COMBO)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    g_iSniperComboHit1016[iAttacker] = true;
    if (bBuilding) return Plugin_Continue;
    g_iSniperCombo1016[iAttacker]++;
    
    decl String:strSound[PLATFORM_MAX_PATH];
    strcopy(strSound, sizeof(strSound), SNIPER_COMBO_1016_1A);
    
    if (g_iSniperCombo1016[iAttacker] <= 1) {
        if (GetRandomInt(0,1) == 0) strcopy(strSound, sizeof(strSound), SNIPER_COMBO_1016_1B);
        fDamage *= DMGBONUS_1016_A;
    }
    else if (g_iSniperCombo1016[iAttacker] == 2) {
        Format(strSound, sizeof(strSound), SNIPER_COMBO_1016_2);
        fDamage *= DMGBONUS_1016_B;
    }
    else if (g_iSniperCombo1016[iAttacker] >= 3) {
        Format(strSound, sizeof(strSound), SNIPER_COMBO_1016_3);
        iDamageType = MakeCritDamageType(iDamageType);
        fDamage *= DMGBONUS_1016_C;
        g_iSniperCombo1016[iAttacker] = 0;
    }
    if (ShouldReveal(iVictim)) {
        EmitSoundToClient(iAttacker, strSound);
    }
    
    return Plugin_Changed;
}
