#include "Interactor.h"
#include "LNR/Component/InfoComponent.h"

AInteractor::AInteractor()
{
	Info = CreateDefaultSubobject<UInfoComponent>("Info");
}

void AInteractor::BeginPlay()
{
	Super::BeginPlay();
	Info->Init();
}

void AInteractor::OnInteract_Implementation(AHero* nHero)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Interact!");
}

void AInteractor::OnShowInfo_Implementation(AHero* nHero, bool val)
{
	Info->Show(val);
}
