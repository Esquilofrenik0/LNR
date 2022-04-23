#include "Human.h"
#include "LNR/Component/ApparelComponent.h"
#include "LNR/Component/AvatarComponent.h"

AHuman::AHuman()
{
	PrimaryActorTick.bCanEverTick = false;
	Apparel = CreateDefaultSubobject<UApparelComponent>("Apparel");
	Apparel->Setup(GetMesh());
	Avatar = CreateDefaultSubobject<UAvatarComponent>("Avatar");
	Avatar->Setup(Apparel);
}

void AHuman::BeginPlay()
{
	Super::BeginPlay();
}