#include "GadgetBase.h"

AGadgetBase::AGadgetBase()
{
	bReplicates = true;
	SetReplicatingMovement(true);
}

void AGadgetBase::ActivateGadget_Implementation(ABody* body, FVector location)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Activate Gadget Implementation!");
}
