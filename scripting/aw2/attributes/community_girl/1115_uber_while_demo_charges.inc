#define ATTRIBUTE_DEMO_UBER_WHILE_CHARGING         1115

new bool:g_bIsOn1115[MAXPLAYERS+1] = false;
new Float:fAttribute_1115_Time[MAXPLAYERS+1] = 0.0;

public Attribute_1115_OnConditionAdded(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Charging) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_DEMO_UBER_WHILE_CHARGING)) return;
 
    new Float:Cond_Check1115 = GetClientAttribute(iClient, _, ATTRIBUTE_DEMO_UBER_WHILE_CHARGING);
    if (Cond_Check1115 <= 1.0)
    {
    TF2_AddCondition(iClient, TFCond_Ubercharged, 2.0);
    }
    else if (Cond_Check1115 == 2.0)
    {
    TF2_AddCondition(iClient, TFCond_DefenseBuffed, 2.0);
    }
    else if (Cond_Check1115 == 3.0)
    {
    TF2_AddCondition(iClient, TFCond_Bonked, 2.0);
    }
    else if (Cond_Check1115 == 4.0)
    {
    TF2_AddCondition(iClient, TFCond_OnFire, 2.0);
    }
    else if (Cond_Check1115 == 5.0)
    {
    TF2_AddCondition(iClient, TFCond_MarkedForDeath, 2.0);
    }
    else if (Cond_Check1115 == 6.0)
    {
    TF2_AddCondition(iClient, TFCond_Ubercharged, 2.0);
    TF2_AddCondition(iClient, TFCond_OnFire, 2.0);
    }
    else if (Cond_Check1115 >= 7.0)
    {
    CreateTimer(1.5, Attribute_1115_Timer, iClient);
    Attribute_1115_Glide(iClient);
    g_bIsOn1115[iClient] = true;
    }
}

public Action:Attribute_1115_Timer(Handle:hTimer, any:iClient) 
{
    if (!IsValidClient(iClient)) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_DEMO_UBER_WHILE_CHARGING)) return;
    
    fAttribute_1115_Time[iClient] = 0.0;
    g_bIsOn1115[iClient] = false;
}

Attribute_1115_Glide(iClient)
{
    if (!IsValidClient(iClient)) return;
    
    while (g_bIsOn1115[iClient]) {
    if (OnGround(iClient))
        {
        fAttribute_1115_Time[iClient] = 0.0;
        }
    if (GetEntityMoveType(iClient) != MOVETYPE_WALK) return;
    
    decl Float:vVelocity[3];
    GetVelocity(iClient, vVelocity);
    
    fAttribute_1115_Time[iClient] += 0.1;
    
    if (fAttribute_1115_Time[iClient] < 1.5)
    {
    new Float:fPush = -11.5;
    
    if (vVelocity[2] > 0)
    {
        vVelocity[2] -= fPush * 0.3;
    }
    else
    {
        vVelocity[2] += fPush * 1.0;
    }
    
    TeleportEntity(iClient, NULL_VECTOR, NULL_VECTOR, vVelocity);
    }
    }
}

public Attribute_1115_OnConditionRemoved(iClient, TFCond:condition)
{
    if (!IsValidClient(iClient)) return;
    if (condition != TFCond_Charging) return;
    if (!ClientHasAttribute(iClient, _, ATTRIBUTE_DEMO_UBER_WHILE_CHARGING)) return;
    
    new Float:Cond_Check1115 = GetClientAttribute(iClient, _, ATTRIBUTE_DEMO_UBER_WHILE_CHARGING);
    if (Cond_Check1115 <= 1.0)
    {
    TF2_RemoveCondition(iClient, TFCond_Ubercharged);
    }
    else if (Cond_Check1115 == 2.0)
    {
    TF2_RemoveCondition(iClient, TFCond_DefenseBuffed);
    }
    else if (Cond_Check1115 == 3.0)
    {
    TF2_RemoveCondition(iClient, TFCond_Bonked);
    }
    else if (Cond_Check1115 == 4.0)
    {
    TF2_RemoveCondition(iClient, TFCond_OnFire);
    }
    else if (Cond_Check1115 == 5.0)
    {
    TF2_RemoveCondition(iClient, TFCond_MarkedForDeath);
    }
    else if (Cond_Check1115 == 6.0)
    {
    TF2_RemoveCondition(iClient, TFCond_Ubercharged);
    TF2_RemoveCondition(iClient, TFCond_OnFire);
    }
    else if (Cond_Check1115 >= 7.0)
    {
    g_bIsOn1115[iClient] = false;
    }
}