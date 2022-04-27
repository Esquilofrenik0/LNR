#include "Human.h"
#include "LNR/AI/Npc.h"
#include "LNR/Component/ApparelComponent.h"
#include "LNR/Component/AvatarComponent.h"

AHuman::AHuman()
{
	Apparel = CreateDefaultSubobject<UApparelComponent>("Apparel");
	Apparel->Setup(GetMesh());
	Avatar = CreateDefaultSubobject<UAvatarComponent>("Avatar");
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
