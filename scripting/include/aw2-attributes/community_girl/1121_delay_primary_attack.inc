#define ATTRIBUTE_HEAT_ENGI     1121

new Float:g_f1121LastHit[MAXPLAYERS+1] = 0.0;
new g_i1121HeatLoss[MAXPLAYERS+1] = 0;

Attribute_1121_Init()
{
    AddRecharge(ATTRIBUTE_HEAT_ENGI, "Shotgun Overheat", _, _, _, false);
}

Attribute_1121_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_HEAT_ENGI)) return;
    if (!IsValidClient(iClient)) return;

    new Float:f1121Random = GetRandomFloat(1.50, 2.25);
    AddClientRecharge(iClient, ATTRIBUTE_HEAT_ENGI, f1121Random);
    
    if (GetClientRecharge(iClient, ATTRIBUTE_HEAT_ENGI) == 100.0) {
    TF2_IgnitePlayer(iClient, iClient);
    AttachParticle(iClient, PARTICLE_SMOKETRAIL1, 10.0);
    }    
}

Attribute_1121_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
if (!ClientHasAttribute(iClient, _, ATTRIBUTE_HEAT_ENGI)) return iButtons;

new Float:f1121Heat = GetClientRecharge(iClient, ATTRIBUTE_HEAT_ENGI);
if (f1121Heat <= 0.0) return iButtons;

g_i1121HeatLoss[iClient] += 1;

if (GetEngineTime() >= g_f1121LastHit[iClient] + 8.0) {
//60 ticks for 1 sec, 30 ticks for 0.5 sec
if (g_i1121HeatLoss[iClient] >= 30) {
AddClientRecharge(iClient, ATTRIBUTE_HEAT_ENGI, -1.0);
g_i1121HeatLoss[iClient] = 0;
}
if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_HEAT_ENGI)) {
if (f1121Heat >= 40.0) {
new weaponentity1121 = GetEntPropEnt(iClient, Prop_Send, "m_hActiveWeapon");
AttachParticle(weaponentity1121, PARTICLE_FIRETRAIL1, 0.5);
}
}
}
return iButtons;
}

public Action:Attribute_1121_OnTakeDamage(iVictim, &iAttacker, iSlot, &Float:fDamage, &iDamageType, Float:fForce[3], Float:fForcePos[3], bool:bBuilding)
{
    if (!IsValidClient(iAttacker)) return Plugin_Continue;    
    if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_HEAT_ENGI)) return Plugin_Continue;
    if (fDamage <= 0.0) return Plugin_Continue;
    
    new Float:fHeat1121 = GetClientRecharge(iAttacker, ATTRIBUTE_HEAT_ENGI);
    new Float:fMinimumShots = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_HEAT_ENGI);
    if (fHeat1121 <= fMinimumShots) {
    fHeat1121 = fMinimumShots;
    }
    
    fDamage *= (fMinimumShots/fHeat1121);
    g_f1121LastHit[iAttacker] = GetEngineTime();
    
    return Plugin_Changed;
}