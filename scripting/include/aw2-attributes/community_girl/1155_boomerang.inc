#define ATTRIBUTE_BOOMERANG      1155

new g_iProjectileBounces1155[MAX_EDICTS+1] = 0;
new g_iBoomerangs[MAXPLAYERS+1] = -1;
new g_iBoomerangLife[MAXPLAYERS+1] = 0;
new Float:g_fBoomerangAim[MAXPLAYERS+1][3];

Attribute_1155_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
	if (ClientHasAttribute(iClient, iSlot, ATTRIBUTE_BOOMERANG))
	{   
        if (iButtons & IN_ATTACK2 == IN_ATTACK2)
		{
           Attributes_ThrowBoomerang(iClient);
		}
	}
	return iButtons;
}

Attributes_ThrowBoomerang(iClient) {
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_BOOMERANG)) return;
    if (GetClientSlot(iClient) != 2) return;
    
    if (g_iBoomerangs[iClient] > 0) return;
    
    Attributes_RemoveBoomerang(iClient, true);
    
    decl Float:fOrigin[3];
    decl Float:fAnglesEye[3];
    GetClientEyePosition(iClient, fOrigin);
    GetClientEyeAngles(iClient, fAnglesEye);
    
    //Get end position
    g_fBoomerangAim[iClient][0] = -999.0;
    //TR_TraceRayFilter(fOrigin, fAnglesEye, MASK_VISIBLE_AND_NPCS, RayType_Infinite, TraceRayDontHitSelf, iClient);
    TR_TraceRayFilter(fOrigin, fAnglesEye, MASK_VISIBLE_AND_NPCS, RayType_Infinite, TraceRayDontHitPlayers);
    if (TR_DidHit(INVALID_HANDLE)) {
        decl Float:fEndPosition[3];
        TR_GetEndPosition(fEndPosition);
        
        g_fBoomerangAim[iClient][0] = fEndPosition[0];
        g_fBoomerangAim[iClient][1] = fEndPosition[1];
        g_fBoomerangAim[iClient][2] = fEndPosition[2];
    }
    
    new iEntity = CreateEntityByName("prop_physics_override");
    if (IsValidEdict(iEntity)) {
        SetEntPropEnt(iEntity, Prop_Data, "m_hOwnerEntity", iClient);
        SetEntityModel(iEntity, MODEL_BOOMERANG);
        DispatchSpawn(iEntity);
        g_iProjectileBounces1155[iEntity] = 0;
        
        decl String:strName[64];
        Format(strName, sizeof(strName), "tf2boomerang");
        DispatchKeyValue(iEntity, "targetname", strName);
        
        decl Float:fAngles[3];
        decl Float:fVelocity[3];
        new Float:fDifference = GetRandomFloat(20.0, 45.0);
        if (GetRandomInt(0,1) == 1) fDifference = fDifference * -1;
        fAnglesEye[1] += fDifference;
        AnglesToVelocity(fAnglesEye, fVelocity, 900.0);
        fAngles[0] = 0.0;
        fAngles[1] = 0.0;
        fAngles[2] = -90.0;
        
        TeleportEntity(iEntity, fOrigin, fAngles, fVelocity);
        
        g_iBoomerangs[iClient] = iEntity;
        g_iBoomerangLife[iClient] = 0;
        
        if (GetClientTeam(iClient) == TEAM_BLUE) {
            AttachParticle(iEntity, "player_intel_trail_blue");
            AttachParticle(iEntity, "critical_grenade_blue_glow");
        }
        if (GetClientTeam(iClient) == TEAM_RED) {
            AttachParticle(iEntity, "player_intel_trail_red");
            AttachParticle(iEntity, "critical_grenade_red_glow");
        }
        
        BoomerangController(iEntity);
        
        ClientCommand(iClient, "lastinv");
        TF2_RemoveWeaponSlot(iClient, 2);
    }
}

public Action:Attribute_1155_PStartTouch(iEntity, iOther, iOwner, iSlot)
{
    if (!ClientHasAttribute(iOwner, iSlot, ATTRIBUTE_BOOMERANG)) return Plugin_Continue;
    if (IsValidClient(iOther)) return Plugin_Continue;
    if (IsEntityBuilding(iOther)) return Plugin_Continue;
    
    new iTotal = 1;
    if (g_iProjectileBounces1155[iEntity] >= iTotal) return Plugin_Continue;
    Attributes_RemoveBoomerang(iOwner);
   
    return Plugin_Handled;
}

Attributes_RemoveBoomerang(iClient, bool:bTerminal = false) {
    new iEntity = g_iBoomerangs[iClient];
    
    g_iBoomerangs[iClient] = -1;
    g_iBoomerangLife[iClient] = 0;
    
    if (IsClassname(iEntity, "prop_physics")) {
        RemoveEdict(iEntity);
    }
    
    if (IsValidClient(iClient) && IsPlayerAlive(iClient) && !bTerminal) {
        EmitSoundToClient(iClient, SOUND_ITEMREADY, _, _, SNDLEVEL_SCREAMING);
        new iClass = GetPlayerClass(iClient);
        ManageClientLoadoutSlot(iClient, iClass, 2);
    }
}

BoomerangController(iEntity) {
    new iClient = GetEntPropEnt(iEntity, Prop_Data, "m_hOwnerEntity");
    
    g_iBoomerangLife[iClient]++;
    if (g_iBoomerangLife[iClient] >= 300) {
        Attributes_RemoveBoomerang(iClient);
        return;
    }
    
    if (IsValidClient(iClient) && IsPlayerAlive(iClient)) {
        decl Float:fVelocity[3];
        //decl Float:fRotation[3];
        //GetEntPropVector(iEntity, Prop_Data, "m_angRotation", fRotation);
        GetEntPropVector(iEntity, Prop_Data, "m_vecAbsVelocity", fVelocity);
        
        new Float:fLength = GetVectorLength(fVelocity);
        if (fLength <= 420.0) {
            Attributes_RemoveBoomerang(iClient);
            return;
        }
        if (g_fBoomerangAim[iClient][0] != -999.0) {
            decl Float:fOrigin[3];
            decl Float:fTargetVector[3];
            decl Float:fMiddleVector[3];
            decl Float:fTargetOrigin[3];
            new Float:fTurn = 0.15;
            
            GetEntPropVector(iEntity, Prop_Data, "m_vecAbsOrigin", fOrigin);
            
            if (g_iBoomerangLife[iClient] >= 80) {
                GetClientEyePosition(iClient, fTargetOrigin);
            } else {
                fTargetOrigin[0] = g_fBoomerangAim[iClient][0];
                fTargetOrigin[1] = g_fBoomerangAim[iClient][1];
                fTargetOrigin[2] = g_fBoomerangAim[iClient][2];
                fTurn = 0.3;
            }

            new Float:fSpeed = 700.0;
            
            SubtractVectors(fTargetOrigin, fOrigin, fTargetVector);
            AddVectors(fVelocity, fTargetVector, fMiddleVector);
            ScaleVector(fMiddleVector, fTurn);
            AddVectors(fVelocity, fMiddleVector, fVelocity);
            NormalizeVector(fVelocity, fVelocity);
            
            //fRotation[2] = -90.0;
            //fRotation[0] = 0.0;
            //fRotation[1] += 20.0;

            ScaleVector(fVelocity, fSpeed);
        }
        fVelocity[2]+= 0.2;
        TeleportEntity(iEntity, NULL_VECTOR, NULL_VECTOR, fVelocity);
    }
    if (g_iBoomerangLife[iClient] >= 20) {
        decl Float:fOriginBoomerang[3];
        decl Float:fOriginTarget[3];
        decl Float:fVelocityTarget[3];
        decl Float:fVelocityBoomerang[3];
        GetEntPropVector(iEntity, Prop_Data, "m_vecAbsOrigin", fOriginBoomerang);
        GetEntPropVector(iEntity, Prop_Data, "m_vecAbsVelocity", fVelocityBoomerang);
        
        for (new iTarget = 0; iTarget <= MaxClients; iTarget++) {
            if (IsValidClient(iTarget)) {
                GetClientEyePosition(iTarget, fOriginTarget);
                if (GetVectorDistance(fOriginBoomerang, fOriginTarget) <= 50.0) {
                    if (iTarget == iClient) {
                        if (g_iBoomerangLife[iClient] >= 80) {
                            Attributes_RemoveBoomerang(iClient);
                            return;
                        }
                    } else {
                        if (GetClientTeam(iClient) != GetClientTeam(iTarget) && IsValidTeam(iTarget)) {
                            new iDamage = GetRandomInt(50,100);
                            DealDamage(iTarget, iDamage, iClient , _, "advanced_sniper_bthrow");
                            
                            GetEntPropVector(iTarget, Prop_Data, "m_vecVelocity", fVelocityTarget);
                            
                            new iSound = GetRandomInt(0,  sizeof(g_strGenericHit)-1);
                            EmitSoundToClient(iTarget, g_strGenericHit[iSound], _, _, SNDLEVEL_ROCKET);
                            EmitSoundToClient(iClient, g_strGenericHit[iSound], _, _, SNDLEVEL_ROCKET);
                            EmitSoundToAll(g_strGenericHit[iSound], iTarget, _, SNDLEVEL_ROCKET);
                            
                            Attributes_RemoveBoomerang(iClient);
                        }
                    }
                }
            }
        }
    }
}