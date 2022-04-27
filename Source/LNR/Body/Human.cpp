#include "Human.h"
#include "LNR/AI/Npc.h"
#include "LNR/Component/ApparelComponent.h"
#include "LNR/Component/AvatarComponent.h"

AHuman::AHuman()
{
	Apparel = CreateDefaultSubobject<UApparelComponent>("Apparel");
	Avatar = CreateDefaultSubobject<UAvatarComponent>("Avatar");
}

void AHuman::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Apparel->Setup(GetMesh());
	Avatar->Setup(Apparel);
}

void AHuman::BeginPlay()
{
	Super::BeginPlay();
	if (Npc)
	{
		Avatar->RandomizeAvatar();
		Avatar->RandomizeOutfit();
	}
}
