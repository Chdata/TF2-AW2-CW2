#define ATTRIBUTE_PROJECTILE_MODEL      1080

#define PROJECTILE_MODEL_1              "models/weapons/w_models/w_stickybomb3.mdl"
#define PROJECTILE_MODEL_2              "models/props_halloween/eyeball_projectile.mdl"
#define PROJECTILE_MODEL_3              "models/weapons/w_models/w_grenade_gas.mdl"
#define PROJECTILE_MODEL_4              "models/weapons/w_models/w_grenade_beartrap.mdl"
#define PROJECTILE_MODEL_5              "models/weapons/w_models/w_grenade_conc.mdl"
#define PROJECTILE_MODEL_6              "models/weapons/w_models/w_grenade_frag.mdl"
#define PROJECTILE_MODEL_7              "models/effects/miniguncasing.mdl"
#define PROJECTILE_MODEL_8              "models/props_forest/dove.mdl"
#define PROJECTILE_MODEL_9              "models/weapons/w_models/w_grenade_bomblet.mdl"
#define PROJECTILE_MODEL_10             "models/props_forest/saw_blade.mdl"
#define PROJECTILE_MODEL_11             "models/props_forest/saw_blade_large.mdl"
#define PROJECTILE_MODEL_12             "models/weapons/c_models/c_madmilk/c_madmilk.mdl"
#define PROJECTILE_MODEL_13             "models/weapons/c_models/c_xms_cold_shoulder/c_xms_cold_shoulder.mdl"
#define PROJECTILE_MODEL_14             "models/weapons/c_models/c_dart.mdl"
#define PROJECTILE_MODEL_15             "models/weapons/w_models/w_baseball.mdl"
#define PROJECTILE_MODEL_16             "models/weapons/w_models/w_drg_ball.mdl"
#define PROJECTILE_MODEL_17             "models/weapons/w_models/w_syringe_proj.mdl"
#define PROJECTILE_MODEL_18             "models/weapons/w_models/w_syringe.mdl"
#define PROJECTILE_MODEL_19             "models/weapons/w_models/w_bottle.mdl"
#define PROJECTILE_MODEL_20             "models/weapons/w_models/w_arrow.mdl"
//21 -24 are currently defined in Attributes.res as Grenade models for the Trinity Grenades
#define PROJECTILE_MODEL_25             "models/weapons/c_models/urinejar.mdl"
#define PROJECTILE_MODEL_26             "models/items/medkit_small.mdl"
#define PROJECTILE_MODEL_27             "models/weapons/c_models/c_sandwich/c_sandwich.mdl"
#define PROJECTILE_MODEL_28             "models/buildables/sentry3_rockets.mdl"
#define PROJECTILE_MODEL_29             "models/weapons/w_missile_launch.mdl"
#define PROJECTILE_MODEL_30             "models/effects/muzzleflash/minigunmuzzle.mdl"
#define PROJECTILE_MODEL_31             "models/effects/sentry1_muzzle/sentry1_muzzle.mdl"

Attribute_1080_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_PROJECTILE_MODEL)) return;
    
    new iModel = RoundFloat(GetClientAttribute(iClient, iSlot, ATTRIBUTE_PROJECTILE_MODEL));
    if (iModel > 28) return;
    
    switch (iModel)
    {
        case 1:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_1);
        }
        case 2:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_2);
        }
        case 3:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_3);
        }
        case 4:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_4);
        }
        case 5:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_5);
        }
        case 6:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_6);
        }
        case 7:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_7);
        }
        case 8:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_8);
        }
        case 9:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_9);
        }
        case 10:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_10);
        }
        case 11:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_11);
        }
        case 12:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_12);
        }
        case 13:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_13);
        }
        case 14:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_14);
        }
        case 15:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_15);
        }
        case 16:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_16);
        }
        case 17:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_17);
        }
        case 18:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_18);
        }
        case 19:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_19);
        }
        case 20:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_20);
        }
        case 25:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_25);
        }
        case 26:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_26);
        }
        case 27:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_27);
        }
        case 28:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_28);
        }
        case 29:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_29);
        }
        case 30:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_30);
        }
        case 31:
        {
            SetEntityModel(iEntity, PROJECTILE_MODEL_31);
        }
    }
}

Attribute_1080_Precache()
{
    SuperPrecacheModel(PROJECTILE_MODEL_1, true);
    SuperPrecacheModel(PROJECTILE_MODEL_2, true);
    SuperPrecacheModel(PROJECTILE_MODEL_3, true);
    SuperPrecacheModel(PROJECTILE_MODEL_4, true);
    SuperPrecacheModel(PROJECTILE_MODEL_5, true);
    SuperPrecacheModel(PROJECTILE_MODEL_6, true);
    SuperPrecacheModel(PROJECTILE_MODEL_7, true);
    SuperPrecacheModel(PROJECTILE_MODEL_8, true);
    SuperPrecacheModel(PROJECTILE_MODEL_9, true);
    SuperPrecacheModel(PROJECTILE_MODEL_10, true);
    SuperPrecacheModel(PROJECTILE_MODEL_11, true);
    SuperPrecacheModel(PROJECTILE_MODEL_12, true);
    SuperPrecacheModel(PROJECTILE_MODEL_13, true);
    SuperPrecacheModel(PROJECTILE_MODEL_14, true);
    SuperPrecacheModel(PROJECTILE_MODEL_15, true);
    SuperPrecacheModel(PROJECTILE_MODEL_16, true);
    SuperPrecacheModel(PROJECTILE_MODEL_17, true);
    SuperPrecacheModel(PROJECTILE_MODEL_18, true);
    SuperPrecacheModel(PROJECTILE_MODEL_19, true);
    SuperPrecacheModel(PROJECTILE_MODEL_20, true);
    SuperPrecacheModel(PROJECTILE_MODEL_25, true);
    SuperPrecacheModel(PROJECTILE_MODEL_26, true);
    SuperPrecacheModel(PROJECTILE_MODEL_27, true);
    SuperPrecacheModel(PROJECTILE_MODEL_28, true);
    SuperPrecacheModel(PROJECTILE_MODEL_29, true);
    SuperPrecacheModel(PROJECTILE_MODEL_30, true);
}
