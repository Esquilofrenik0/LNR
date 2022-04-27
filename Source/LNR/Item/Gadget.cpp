#include "Gadget.h"
#include "LNR/Body/Body.h"
#include "LNR/Gadget/GadgetBase.h"

void UGadget::Consume_Implementation(ABody* body)
{
	FVector loc = body->GetMesh()->GetSocketLocation("RightHand");
	AGadgetBase* gb = Cast<AGadgetBase>(body->SpawnActor(Gadget, loc, FRotator()));
	gb->ActivateGadget(body, loc);
}
