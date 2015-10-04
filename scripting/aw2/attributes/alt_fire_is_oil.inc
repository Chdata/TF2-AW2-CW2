#define ATTRIBUTE_ALT_FIRE_IS_OIL       1056

#define ATTRIBUTE_FIRELEAK_TIME         0.2
#define ATTRIBUTE_FIRELEAK_COST         10

#define MODEL_FIRELEAK                  "models/props_farm/haypile001.mdl"

new Float:g_fOilLeakDelay[MAXPLAYERS+1] = 0.0;
new g_iOilLeakStatus[MAX_EDICTS + 1] = 0;
new g_iOilLeakDamage[MAXPLAYERS+1] = 0;
new g_iOilLeakDamageOwner[MAXPLAYERS+1] = 0;
new Float:g_fOilLeakLife[MAX_EDICTS + 1] = 0.0;

new Handle:g_hOilLeakEntities = INVALID_HANDLE;

Attribute_1056_Init()
{
    g_hOilLeakEntities = CreateArray();
}


Attribute_1056_Precache()
{
    SuperPrecacheModel(MODEL_FIRELEAK);
}

Attribute_1056_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_ALT_FIRE_IS_OIL))
    {
        if (iButtons & IN_ATTACK2 == IN_ATTACK2)
        {
            Attribute_1056_OilLeak(iClient, iSlot);
            if (GetClientTeam(iClient) == TEAM_SPEC) {return iButtons;}
        }

    }
    
    if (GetFlamethrowerStrength(iClient) >= 2)
    {
        decl Float:vOrigin[3];
        GetClientAbsOrigin(iClient, vOrigin);
        Attribute_1056_IgniteLeak(vOrigin);
    }
    
    new iAttacker = g_iOilLeakDamageOwner[iClient];
    if (IsValidClient(iAttacker))
    {
        //PrintToChat(iClient, "Hurt by %N's fire", iAttacker);
        //DealDamage(iClient, 10 + g_iOilLeakDamage[iClient] * 2, iAttacker, TF_WEAPON_FLAMETHROWER);
        DealDamage(iClient, 2 + g_iOilLeakDamage[iClient] * 2, iAttacker, _, "firedeath");
        if (GetPlayerClass(iClient) != CLASS_PYRO) TF2_IgnitePlayer(iClient, iAttacker);
        g_iOilLeakDamage[iClient]++;
    }
    else
    {
        g_iOilLeakDamage[iClient] -= 4;
        if (g_iOilLeakDamage[iClient] < 0) g_iOilLeakDamage[iClient] = 0;
    }
    g_iOilLeakDamageOwner[iClient] = -1;
    
    return iButtons;
}

Attribute_1056_OilLeak(iClient, iSlot)
{
    if (g_fOilLeakDelay[iClient] >= GetEngineTime() - ATTRIBUTE_FIRELEAK_TIME) return;
    if (!SubtractWeaponAmmo(iClient, iSlot, ATTRIBUTE_FIRELEAK_COST)) return;
    
    g_fOilLeakDelay[iClient] = GetEngineTime();
    
    if (g_hOilLeakEntities == INVALID_HANDLE) g_hOilLeakEntities = CreateArray();
    
    new iEntity = CreateEntityByName("prop_physics_override");
    if (IsValidEdict(iEntity)) {
        SetEntPropEnt(iEntity, Prop_Data, "m_hOwnerEntity", iClient);
        SetEntityModel(iEntity, MODEL_DEFAULTPHYSICS);
        DispatchSpawn(iEntity);
        
        AcceptEntityInput(iEntity, "DisableCollision");
        SetEntityRenderMode(iEntity, RENDER_TRANSCOLOR);
        SetEntityRenderColor(iEntity, _, _, _, 0);
        
        decl String:strName[64];
        Format(strName, sizeof(strName), "tf2leak");
        DispatchKeyValue(iEntity, "targetname", strName);
        
        decl Float:fAngles[3], Float:fVelocity[3], Float:fOrigin[3];
        GetClientEyePosition(iClient, fOrigin);
        GetClientEyeAngles(iClient, fAngles);
        AnglesToVelocity(fAngles, fVelocity, 600.0);
        
        TeleportEntity(iEntity, fOrigin, fAngles, fVelocity);
        
        if (GetClientTeam(iClient) == TEAM_BLUE) {
            AttachParticle(iEntity, "peejar_trail_blu");
            AttachParticle(iEntity, "peejar_trail_blu");
            AttachParticle(iEntity, "peejar_trail_blu");
            AttachParticle(iEntity, "peejar_trail_blu");
            AttachParticle(iEntity, "peejar_trail_blu");
            AttachParticle(iEntity, "peejar_trail_blu");
            AttachParticle(iEntity, "peejar_trail_blu");
        }
        if (GetClientTeam(iClient) == TEAM_RED) {
            AttachParticle(iEntity, "peejar_trail_red");
            AttachParticle(iEntity, "peejar_trail_red");
            AttachParticle(iEntity, "peejar_trail_red");
            AttachParticle(iEntity, "peejar_trail_red");
            AttachParticle(iEntity, "peejar_trail_red");
            AttachParticle(iEntity, "peejar_trail_red");
            AttachParticle(iEntity, "peejar_trail_red");
        }
        
        g_fOilLeakLife[iEntity] = GetEngineTime() + 15.0;
        g_iOilLeakStatus[iEntity] = 0;
        //PrintToChatAll("hooked");
        
        PushArrayCell(g_hOilLeakEntities, iEntity);
    }
}

Attributes_1056_Think(bool:bTerminate = false)
{
    if (g_hOilLeakEntities == INVALID_HANDLE) return;
    
    new iClientLeaks[MAXPLAYERS+1] = 0;
    
    for (new i = GetArraySize(g_hOilLeakEntities)-1; i >= 0; i--)
    {
        new iEntity = GetArrayCell(g_hOilLeakEntities, i);
        new iOwner = Attribute_1056_OilThink(iEntity);
        if (bTerminate || iOwner < 0 || iClientLeaks[iOwner] > 15)
        {
            if (IsClassname(iEntity, "prop_physics")) AcceptEntityInput(iEntity, "kill");
            RemoveFromArray(g_hOilLeakEntities, i);
        }
        else
        {
            iClientLeaks[iOwner]++;
        }
    }
    
    if (bTerminate) CloseHandle(g_hOilLeakEntities);
}

Attribute_1056_OilThink(iEntity)
{
    if (!IsClassname(iEntity, "prop_physics")) return -1;
    
    new iOwner = GetEntPropEnt(iEntity, Prop_Send, "m_hOwnerEntity");
    if (!IsValidClient(iOwner)) return -1;
    
    new Float:fLife = g_fOilLeakLife[iEntity];
    if (GetEngineTime() >= fLife) return -1;
    
    
    decl Float:vOrigin[3];
    GetEntityOrigin(iEntity, vOrigin);
    
    if (g_iOilLeakStatus[iEntity] == 0) {
        new Float:vAngleDown[3];
        vAngleDown[0] = 90.0;
        new Handle:hTrace = TR_TraceRayFilterEx(vOrigin, vAngleDown, MASK_PLAYERSOLID, RayType_Infinite, TraceRayDontHitPlayers);
        if (TR_DidHit(hTrace)) {
            decl Float:vEnd[3];
            TR_GetEndPosition(vEnd, hTrace);
            if (GetVectorDistance(vEnd, vOrigin) / 50.0 <= 0.4) {
                new Float:vStop[3];
                SetEntityMoveType(iEntity, MOVETYPE_NONE);
                TeleportEntity(iEntity, vEnd, NULL_VECTOR, vStop);
                
                SetEntityRenderColor(iEntity, _, _, _, 255);
                SetEntityRenderMode(iEntity, RENDER_NONE);
                SetEntityModel(iEntity, MODEL_FIRELEAK);
                g_iOilLeakStatus[iEntity] = 1;
            }
        }
        CloseHandle(hTrace);
    }
    if (g_iOilLeakStatus[iEntity] == 2) {
        decl Float:vClientOrigin[3];
        for (new iClient = 0; iClient <= MaxClients; iClient++) {
            if (IsValidClient(iClient) && IsPlayerAlive(iClient) && (GetClientTeam(iClient) != GetClientTeam(iOwner) || iClient == iOwner)) {
                GetClientAbsOrigin(iClient, vClientOrigin);
                if (GetVectorDistance(vOrigin, vClientOrigin) / 50.0 <= 1.5) {
                    //PrintToChat(iClient, "HELLO %N", iOwner);
                    g_iOilLeakDamageOwner[iClient] = iOwner;
                }
            }
        }
    }
    
    return iOwner;
}

Attribute_1056_OnProjectile(iEntity, &iClient, &iSlot)
{
    if (!IsClassname(iEntity, "tf_projectile_flare")) return;
    
    decl Float:vOrigin[3];
    GetEntityOrigin(iEntity, vOrigin);
    
    Attribute_1056_IgniteLeak(vOrigin);
}

Attributes_1056_Stop()
{
    Attributes_1056_Think(true);
}

Attribute_1056_IgniteLeak(Float:vPos[3]) {
    decl Float:vOrigin[3];
    decl Float:vFire[3];
    for (new i = GetArraySize(g_hOilLeakEntities)-1; i >= 0; i--)
    {
        new iEntity = GetArrayCell(g_hOilLeakEntities, i);
        
        if (IsClassname(iEntity, "prop_physics"))
        {
            GetEntityOrigin(iEntity, vOrigin);
            new iOwner = GetEntPropEnt(iEntity, Prop_Send, "m_hOwnerEntity");
            if (g_iOilLeakStatus[iEntity] == 1 && GetVectorDistance(vOrigin, vPos) / 50.0 <= 3.0)
            {
                g_iOilLeakStatus[iEntity] = 2;
                g_fOilLeakLife[iEntity] = GetEngineTime() + 5.0;
                Attribute_1056_IgniteLeak(vOrigin);
                vFire[2] = 5.0;
                
                vFire[0] = 22.0;
                vFire[1] = 22.0;
                AttachParticle(iEntity, PARTICLE_FIRE, _, vFire);
                
                vFire[0] = 22.0;
                vFire[1] = -22.0;
                AttachParticle(iEntity, PARTICLE_FIRE, _, vFire);
                
                vFire[0] = -22.0;
                vFire[1] = 22.0;
                AttachParticle(iEntity, PARTICLE_FIRE, _, vFire);
                
                vFire[0] = -22.0;
                vFire[1] = -22.0;
                AttachParticle(iEntity, PARTICLE_FIRE, _, vFire);
                
                vFire[0] = 0.0;
                vFire[1] = 0.0;
                AttachParticle(iEntity, PARTICLE_FIRE, _, vFire);
                
                new String:strParticle[255];
                if (GetClientTeam(iOwner) == TEAM_BLUE) Format(strParticle, sizeof(strParticle), "%s", PARTICLE_AREA_FIRE_BLUE);
                if (!StrEqual(strParticle, "")) AttachParticle(iEntity, strParticle, _, vFire);
            }
        }
    }
}