#define ATTRIBUTE_PARENT_PARTICLES_TEST        1098

Attribute_1098_ProjCreated(iEntity, iClient, iSlot)
{
    if (!ClientHasAttribute(iClient, iSlot, ATTRIBUTE_PARENT_PARTICLES_TEST)) return;
    if (!IsValidEdict(iEntity)) return;
    
    new Float:f1098Time = GetClientAttribute(iClient, iSlot, ATTRIBUTE_PARENT_PARTICLES_TEST);
    AttachParticle(iEntity, PARTICLE_STEAM_ZSTREAM, f1098Time);
}