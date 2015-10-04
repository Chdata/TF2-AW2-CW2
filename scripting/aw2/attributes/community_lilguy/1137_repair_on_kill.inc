#define ATTRIBUTE_REPAIR_ON_KILL		1137

new String:g_strBuildings[5][PLATFORM_MAX_PATH] = {
	"obj_sentrygun",
	"obj_dispenser",
	"obj_teleporter",
	"obj_teleporter_entrance",
	"obj_teleporter_exit"
};

Attribute_1137_OnDeath(iClient, &iAttacker, &iAssister, iSlot) {
	if (!IsValidClient(iAttacker)) return;
	if (!ClientHasAttribute(iAttacker, iSlot, ATTRIBUTE_REPAIR_ON_KILL)) return;
	if (iAttacker == iClient) return;
	if (!IsPlayerAlive(iAttacker)) return;
	
	//DEBUG ON KILL
	PrintToChat(iAttacker, "You killed someone");

	//Percent value
	new Float:fValue = GetClientAttribute(iAttacker, iSlot, ATTRIBUTE_REPAIR_ON_KILL);

	new iEntity;
	new iOwner;
	new iSapper;
	new iLevel;
	//Zero is false, non-zero is true
	new bSapped;
	//Sentry iStates: 1 idle, 2 attacking, 3 upgrading
	new iState;
	new iHealth;
	new iMaxHealth;
	new iAmmoShells;
	new iAmmoRockets;

	//Each building type
	for (new iLoop = 0; iLoop < sizeof(g_strBuildings); iLoop++) {
		//Set default start value
		iEntity = -1;
		//Search through entities of type, then check owner to do stuff
		while ((iEntity = FindEntityByClassname2(iEntity, g_strBuildings[iLoop])) != -1) {
			if (IsValidEdict(iEntity)) {
				iOwner = GetEntPropEnt(iEntity, Prop_Send, "m_hBuilder");
				if (iOwner == iAttacker) {
					bSapped = GetEntProp(iEntity, Prop_Send, "m_bHasSapper");
					//Get state of sentry
					if (StrEqual(g_strBuildings[iLoop], "obj_sentrygun")) {
						iState = GetEntProp(iEntity, Prop_Send, "m_iState");
					} else {

						iState = -1;
					}
					//Has a sapper
					if (bSapped >= 1) {

						//DEBUG FOUND SAPPER
						PrintToChat(iOwner, "%s is sapped", g_strBuildings[iLoop]);

						iSapper = -1;
						while ((iSapper = FindEntityByClassname2(iSapper, "obj_attachment_sapper")) != -1) {
							if (IsValidEdict(iSapper)) {
								AcceptEntityInput(iSapper, "Kill");
							}
						}
					}
					//Repair
					iHealth = GetEntProp(iEntity, Prop_Send, "m_iHealth");
					iMaxHealth = GetEntProp(iEntity, Prop_Send, "m_iMaxHealth");
					iHealth = iHealth + RoundFloat(fValue * float(iMaxHealth));
					if (iHealth > iMaxHealth) iHealth = iMaxHealth;
					SetEntProp(iEntity, Prop_Send, "m_iHealth", iHealth);
					//If sentry in valid state and not upgrading
					if (iState > -1 && iState <= 2) {
						iLevel = GetEntProp(iEntity, Prop_Send, "m_iUpgradeLevel");
						iAmmoShells = GetEntProp(iEntity, Prop_Send, "m_iAmmoShells");
						if (iLevel >= 3) {
							iAmmoShells = iAmmoShells + RoundFloat(fValue * 200.0);
							if (iAmmoShells > 200) iAmmoShells = 200;
							iAmmoRockets = GetEntProp(iEntity, Prop_Send, "m_iAmmoRockets") + RoundFloat(fValue * 20.0);
							if (iAmmoRockets > 20) iAmmoRockets = 20;
							SetEntProp(iEntity, Prop_Send, "m_iAmmoRockets", iAmmoRockets);
						} else if (iLevel == 2) {
							iAmmoShells = iAmmoShells + RoundFloat(fValue * 200.0);
							if (iAmmoShells > 200) iAmmoShells = 200;
						} else {
							iAmmoShells = iAmmoShells + RoundFloat(fValue * 150.0);
							if (iAmmoShells > 150) iAmmoShells = 150;
						}
						SetEntProp(iEntity, Prop_Send, "m_iAmmoShells", iAmmoShells);
					}
				}
			}
		}
	}
	return;
}
