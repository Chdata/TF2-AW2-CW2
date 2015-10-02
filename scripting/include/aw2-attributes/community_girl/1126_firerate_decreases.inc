#define ATTRIBUTE_FIRERATE_OVERHEATS      1126

new Float:g_fFireRateAmount1126[MAXPLAYERS+1] = 0.0;
new bool:g_bExpired[MAXPLAYERS+1] = false;

Attribute_1126_OnInventory(iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FIRERATE_OVERHEATS)) return;
    g_fFireRateAmount1126[iClient] = 0.0;
    new Float:fMAS = GetClientAttribute(iClient, iSlot, ATTRIBUTE_FIRERATE_OVERHEATS);
    new iWeapon = GetPlayerWeaponSlot(iClient, iSlot);
    SetEntPropFloat(iWeapon, Prop_Send, "m_flNextPrimaryAttack", fMAS);
}

Attribute_1126_OnAttack(iClient, iSlot, &bool:bCrit)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_FIRERATE_OVERHEATS)) return;
    
    if (g_bExpired[iClient])
    {
    new iWeapon = GetPlayerWeaponSlot(iClient, iSlot);
    new Float:fMAS = (GetClientAttribute(iClient, iSlot, ATTRIBUTE_FIRERATE_OVERHEATS));
    new Float:GTime = GetGameTime();
    new Float:ResetTime = (GetEntPropFloat(iWeapon, Prop_Send, "m_flNextPrimaryAttack") - GTime) * fMAS + GTime;
    SetEntPropFloat(iWeapon, Prop_Send, "m_flNextPrimaryAttack", ResetTime);
    }
    
    new Float:fMAS = GetClientAttribute(iClient, iSlot, ATTRIBUTE_FIRERATE_OVERHEATS);
    new iWeapon = GetPlayerWeaponSlot(iClient, iSlot);
    
    g_fFireRateAmount1126[iClient] += 0.1;
        
    decl Float:SlowTime;
    new Float:ETime = GetGameTime();
    fMAS += 0.015;
    SlowTime = (GetEntPropFloat(iWeapon, Prop_Send, "m_flNextPrimaryAttack") - ETime) * fMAS + ETime;
    SetEntPropFloat(iWeapon, Prop_Send, "m_flNextPrimaryAttack", SlowTime);
    CreateTimer(2.5, Attribute_1126_Expire, iClient);
    g_bExpired[iClient] = false;
}

public Action:Attribute_1126_Expire(Handle:hTimer, any:iClient) 
{
	if (!IsValidClient(iClient))
	{
		return Plugin_Stop;
	}
	if (g_fFireRateAmount1126[iClient] > 0.0) 
	{
        g_bExpired[iClient] = true;
	}
    
	return Plugin_Continue;
}