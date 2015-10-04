#define ATTRIBUTE_TRIPLE_ARROW          1172

//Most of this script is credit to linux_lower. http://pastebin.com/94urwyzP

//This attribute is fairly comprehensive so it should be a good learning tool for people to study.

new g_i1172TripleShotArrow[MAX_EDICTS+1] = -1;
new Handle:g_h1172TripleShotTimer[MAXPLAYERS+1] = INVALID_HANDLE;
new g_iClient1172[MAXPLAYERS+1] = -1;

Attribute_1172_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_TRIPLE_ARROW)) return;
    if (!IsValidEdict(iEntity)) return;
    
    g_iClient1172[iClient] = iClient;
    EntIndexToEntRef(iEntity);
    new Float:fTime1172 = GetClientAttribute(iClient, iSlot, ATTRIBUTE_TRIPLE_ARROW);
    CreateTimer(fTime1172, Triple_ArrowInit, iEntity);
}

public Action:Triple_ArrowInit(Handle:hTimer, any:iEntRef) 
{
    new iEntity = EntRefToEntIndex(iEntRef);
    if (!IsValidEdict(iEntity)) return;
    
    new iClient = g_iClient1172[iClient];
    g_i1172TripleShotArrow[iEntity] = iEntity;
    g_h1172TripleShotTimer[iClient] = CreateTimer(0.1, TripleArrowCreateOthers, iEntity);
    if (g_h1172TripleShotTimer[iClient] == INVALID_HANDLE) 
    {
    PrintToChatAll("Triple Shot just broke :("); return;
    }
}
    
public Action:TripleArrowCreateOthers(Handle:Timer, any: iEntRef) {
    new iEntity = EntRefToEntIndex(iEntRef);
    new iOwner = GetEntPropEnt(iEntity, Prop_Send, "m_hOwnerEntity");
    new iArrow = g_i1172TripleShotArrow[iEntity];
    
    if (iArrow == -1)
    {
        g_h1172TripleShotTimer[iOwner] = INVALID_HANDLE;
        g_i1172TripleShotArrow[iArrow] = -1;
        return Plugin_Handled;
    }
    new Float:pos[3], Float:vel[3], Float:ang[3];
    GetEntPropVector(iArrow, Prop_Send, "m_vInitialVelocity", vel);
    //If the iArrow is not moving yet then reset the timer
    if (vel[0] == 0 && vel[1] == 0 && vel[2] == 0) 
    {
        g_h1172TripleShotTimer[iOwner] = CreateTimer(0.1, TripleArrowCreateOthers, iOwner);
        if (g_h1172TripleShotTimer[iOwner] == INVALID_HANDLE) {
            g_i1172TripleShotArrow[iArrow] = -1;
            PrintToChatAll("Triple Shot just broke worser :(");
        }
        return Plugin_Handled;
    }
    
    //Otherwise get the position and angle data
    GetEntPropVector(iArrow, Prop_Data, "m_vecAbsOrigin", pos);
    GetEntPropVector(iArrow, Prop_Data, "m_angRotation", ang);
    new Float:degreesToAlterNewArrows = 0.02;//0.26179938; //(Pi / 12) radians == 15 degrees
    new Float:vel2D[3], Float:PerpendicularVector[3];
    vel2D[0] = vel[0];
    vel2D[1] = vel[1];
    vel2D[2] = 0.0;
    new Float:vel_angOriginal = GetAngle(vel);
    new Float:vel_strOriginal = GetVectorLength(vel2D);
    NormalizeVector(vel, PerpendicularVector);
    PerpendicularVector[1] *= -1;
    ScaleVector(PerpendicularVector, 10.0);
    
    /* Create the left iArrow */
    new Float:vel_angLeft = vel_angOriginal - degreesToAlterNewArrows;
    if (vel_angLeft > 6.2831853) {
        vel_angLeft -= 6.2831853;
    }
    new Float:leftPos[3], Float:leftVel[3], Float:leftAng[3], Float:leftVelNormalized[3];
    leftPos[0] = pos[0] - 5.0;
    leftPos[1] = (leftPos[0] / pos[0]) * pos[1];
    leftPos[2] = pos[2];
    //AddVectors(PerpendicularVector, pos, leftPos);
    leftVel[0] = Sine(vel_angLeft) * vel_strOriginal;
    leftVel[1] = Cosine(vel_angLeft) * vel_strOriginal;
    leftVel[2] = vel[2];
    NormalizeVector(leftVel, leftVelNormalized);
    GetVectorAngles(leftVelNormalized, leftAng);

    //Create the iArrow
    new newLeftArrow = CreateEntityByName("tf_projectile_arrow");
    if (newLeftArrow == -1) {PrintToChatAll("OMFG LEFT ARROW CREATION ERROR");}
    
    TeleportEntity(newLeftArrow, leftPos, leftAng, leftVel);
    
    //Set all of the properties up (TODO: get the trail effect on the iArrow to appear)
    //new String:modelName[255];
    //GetEntPropString(iArrow, Prop_Data, "m_ModelName", modelName, sizeof(modelName));
    //SetEntPropString(newLeftArrow, Prop_Data, "m_ModelName", modelName);
    
    //new m_Offset=FindDataMapOffs(iArrow,"m_pfnTouch"); //Find the offset
    //new entvalue=GetEntData(iArrow,m_Offset,4); //Get the value of m_pfnTouch
    //SetEntData(newLeftArrow, m_Offset, entvalue, 4, true); //Set the value of m_pfnTouch to original iArrow's
    
    SetEntityGravity(newLeftArrow, GetEntityGravity(iArrow));
    //SetEntProp(newLeftArrow, Prop_Data, "m_fFlags",  GetEntProp(iArrow, Prop_Data, "m_fFlags"));
    //SetEntPropFloat(newLeftArrow, Prop_Data, "m_flGravity",  0.001);
    SetEntProp(newLeftArrow, Prop_Data, "m_iInitialTeamNum",  GetEntProp(iArrow, Prop_Data, "m_iInitialTeamNum"));
    SetEntProp(newLeftArrow, Prop_Data, "m_iTeamNum", GetEntProp(iArrow, Prop_Data, "m_iTeamNum"));
    SetEntProp(newLeftArrow, Prop_Send, "m_iTeamNum", GetEntProp(iArrow, Prop_Send, "m_iTeamNum"));
    SetEntPropEnt(newLeftArrow, Prop_Data, "m_hOwnerEntity", GetEntPropEnt(iArrow, Prop_Data, "m_hOwnerEntity"));
    SetEntPropEnt(newLeftArrow, Prop_Send, "m_hOwnerEntity", GetEntPropEnt(iArrow, Prop_Send, "m_hOwnerEntity"));
    SetEntPropVector(newLeftArrow, Prop_Send, "m_vInitialVelocity", leftVel);
    SetEntProp(newLeftArrow, Prop_Data, "m_CollisionGroup",  GetEntProp(iArrow, Prop_Data, "m_CollisionGroup"));
    SetEntProp(newLeftArrow, Prop_Send, "m_CollisionGroup",  GetEntProp(iArrow, Prop_Send, "m_CollisionGroup"));
    //SetEntProp(newLeftArrow, Prop_Send, "movecollide",  GetEntProp(iArrow, Prop_Send, "movecollide"));
    //new String:a[100], String:b[100];
    //GetEntPropString(iArrow, Prop_Data, "m_ModelName", a, 100);
    //GetEntPropString(newLeftArrow, Prop_Data, "m_ModelName", b, 100);
    //PrintToChatAll("%s 1%s1", a, b);
    //PrintToChatAll("%.6f %.6f", GetEntPropFloat(iArrow, Prop_Data, "m_flDissolveStartTime"),  GetEntPropFloat(newLeftArrow, Prop_Data, "m_flDissolveStartTime"));
    //PrintToChatAll("%d %d", GetEntPropEnt(iArrow, Prop_Data, "m_hMoveChild"),  GetEntPropEnt(newLeftArrow, Prop_Data, "m_hMoveChild"));
    /*
    new iTeam = GetEntProp(iArrow, Prop_Data, "m_iTeamNum");
    SetVariantInt(iTeam);
    AcceptEntityInput(newLeftArrow, "TeamNum", -1, -1, 0);
    
    SetVariantInt(iTeam);
    AcceptEntityInput(newLeftArrow, "SetTeam", -1, -1, 0);
    */
    DispatchSpawn(newLeftArrow);
    new Float:x[3];
    x[0] = 0.0;
    x[1] = 0.0;
    x[2] = 0.0;
    TeleportEntity(iArrow, x, x,x);
    
    /*
    //Spawn the iArrow and place it
    if (DispatchSpawn(newLeftArrow)) {
        SetEntPropVector (newLeftArrow, Prop_Data, "m_angRotation", leftAng);
        SetEntPropVector(newLeftArrow, Prop_Data, "m_vecAbsVelocity", leftVel);
        SetEntPropVector(newLeftArrow, Prop_Data, "m_vecAbsOrigin", leftPos);
    } else {
        PrintToChatAll("Could not spawn the left iArrow... %d", iArrow);
    }
    
    PerpendicularVector[0] *= -1;
    PerpendicularVector[1] *= -1;
    
    new Float:vel_angRight = vel_angOriginal + degreesToAlterNewArrows;
    if (vel_angRight > 6.2831853)
        vel_angRight -= 6.2831853;
    new Float:rightPos[3], Float:rightVel[3], Float:rightAng[3], Float:rightVelNormalized[3];
    rightPos[0] = pos[0] + 5.0;
    rightPos[1] = (rightPos[0] / pos[0]) * pos[1];
    rightPos[2] = pos[2];
    //AddVectors(PerpendicularVector, pos, rightPos);
    rightVel[0] = Sine(vel_angRight) * vel_strOriginal;
    rightVel[1] = Cosine(vel_angRight) * vel_strOriginal;
    rightVel[2] = vel[2];
    NormalizeVector(rightVel, rightVelNormalized);
    GetVectorAngles(rightVelNormalized, rightAng);

    //Create the iArrow
    new newRightArrow = CreateEntityByName("tf_projectile_arrow");
    if (newRightArrow == -1) {PrintToChatAll("OMFG RIGHT ARROW CREATION ERROR");}
    
    //Set all of the properties up (TODO: get the trail effect on the iArrow to appear)
    SetEntProp(newRightArrow, Prop_Data, "m_iTeamNum", GetClientTeam(iClient));
    SetEntPropEnt(newRightArrow, Prop_Data, "m_hOwnerEntity", iClient);
    SetEntPropVector(newRightArrow, Prop_Send, "m_vInitialVelocity", rightVel);
    SetEntProp(newRightArrow, Prop_Send, "m_CollisionGroup",  GetEntProp(iArrow, Prop_Send, "m_CollisionGroup"));
    SetEntProp(newRightArrow, Prop_Send, "movecollide",  GetEntProp(iArrow, Prop_Send, "movecollide"));
    SetEntPropFloat(newRightArrow, Prop_Data, "m_flGravity",  GetEntPropFloat(iArrow, Prop_Data, "m_flGravity"));
    
    //Spawn the iArrow and place it
    if (DispatchSpawn(newRightArrow)) {
        SetEntPropVector (newRightArrow, Prop_Data, "m_angRotation", rightAng);
        SetEntPropVector(newRightArrow, Prop_Data, "m_vecAbsVelocity", rightVel);
        SetEntPropVector(newRightArrow, Prop_Data, "m_vecAbsOrigin", rightPos);
    } else {
        PrintToChatAll("Could not spawn the right iArrow... %d", iArrow);
    }
    */
    
    //Rid our unnecessary variables of their burdens
    g_h1172TripleShotTimer[iOwner] = INVALID_HANDLE;
    g_i1172TripleShotArrow[iArrow] = -1;

    return Plugin_Handled;
}
