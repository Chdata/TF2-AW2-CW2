#define ATTRIBUTE_MEET_THE_SPY         1116

Attribute_1116_Prethink(iClient, &iButtons, &iSlot, &iButtonsLast)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_MEET_THE_SPY)) return iButtons;

    new Float:fDuration = GetClientAttribute(iClient, iSlot, ATTRIBUTE_MEET_THE_SPY);

    new iClass = -1;
    new iTeam = -1;
    
    if (IsDisguised(iClient)) {
    iClass = GetEntProp(iClient, Prop_Send, "m_nDisguiseClass", iClass);
    iTeam = GetEntProp(iClient, Prop_Send, "m_nDisguiseTeam", iTeam);
    }
    
    new iEntity = CreateEntityByName("prop_dynamic");
    SetEntPropEnt(iEntity, Prop_Data, "m_hOwnerEntity", iClient);
    SetEntityModel(iEntity, "models/player/spy.mdl");
    if (iClass == 1) {
    SetEntityModel(iEntity, "models/player/scout.mdl");
    }
    else if (iClass == 2) {
    SetEntityModel(iEntity, "models/player/sniper.mdl");
    }
    else if (iClass == 3) {
    SetEntityModel(iEntity, "models/player/soldier.mdl");
    }
    else if (iClass == 4) {
    SetEntityModel(iEntity, "models/player/demo.mdl");
    }
    else if (iClass == 5) {
    SetEntityModel(iEntity, "models/player/medic.mdl");
    }
    else if (iClass == 6) {
    SetEntityModel(iEntity, "models/player/heavy.mdl");
    }
    else if (iClass == 7) {
    SetEntityModel(iEntity, "models/player/pyro.mdl");
    }
    else if (iClass == 8) {
    SetEntityModel(iEntity, "models/player/spy.mdl");
    }
    else if (iClass == 9) {
    SetEntityModel(iEntity, "models/player/engineer.mdl");
    }
    
    DispatchSpawn(iEntity);
    AcceptEntityInput(iEntity, "DisableCollision");
    SetEntProp(iEntity, Prop_Send, "m_nSkin", GetClientTeam(iClient));
    if (IsDisguised(iClient)) {
    SetEntProp(iEntity, Prop_Send, "m_nSkin", iTeam);
    }
    
    decl Float:fAngles[3], Float:fVelocity[3], Float:fOrigin[3];
    GetClientEyePosition(iClient, fOrigin);
    GetClientEyeAngles(iClient, fAngles);
    AnglesToVelocity(fAngles, fVelocity, 600.0);
    TeleportEntity(iEntity, fOrigin, fAngles, fVelocity);
    //Animations
    
    new iRandomInt = GetRandomInt(0,5);
    if (iRandomInt == 0) {    
    SetVariantString("Stand_MELEE_ALLCLASS");
    AcceptEntityInput(iEntity, "SetDefaultAnimation");
    SetVariantString("Stand_MELEE_ALLCLASS");
    AcceptEntityInput(iEntity, "SetAnimation");
    }
    else if (iRandomInt == 1) {    
    SetVariantString("taunt01");
    AcceptEntityInput(iEntity, "SetDefaultAnimation");
    SetVariantString("taunt01");
    AcceptEntityInput(iEntity, "SetAnimation");
    }
    else if (iRandomInt == 2) {    
    SetVariantString("taunt02");
    AcceptEntityInput(iEntity, "SetDefaultAnimation");
    SetVariantString("taunt02");
    AcceptEntityInput(iEntity, "SetAnimation");
    }
    else if (iRandomInt == 3) {    
    SetVariantString("taunt03");
    AcceptEntityInput(iEntity, "SetDefaultAnimation");
    SetVariantString("taunt03");
    AcceptEntityInput(iEntity, "SetAnimation");
    }
    else if (iRandomInt == 4) {    
    SetVariantString("taunt04");
    AcceptEntityInput(iEntity, "SetDefaultAnimation");
    SetVariantString("taunt04");
    AcceptEntityInput(iEntity, "SetAnimation");
    }
    else if (iRandomInt == 5) {    
    SetVariantString("taunt05");
    AcceptEntityInput(iEntity, "SetDefaultAnimation");
    SetVariantString("taunt05");
    AcceptEntityInput(iEntity, "SetAnimation");
    }
    
    EntIndexToEntRef(iEntity);
    CreateTimer(fDuration, RemoveFakeSpy, iEntity);
    
    return iButtons;
}

public Action:RemoveFakeSpy(Handle:hTimer, any:iEntRef) 
{
    new iEntity = EntRefToEntIndex(iEntRef);
    if (!IsValidEdict(iEntity)) return;
    
    if (IsClassname(iEntity, "prop_physics")) AcceptEntityInput(iEntity, "kill");
}