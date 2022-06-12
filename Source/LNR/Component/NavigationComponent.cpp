#include "NavigationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LNR/Interface/Marked.h"
#include "LNR/Component/MarkerComponent.h"

UNavigationComponent::UNavigationComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UNavigationComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UNavigationComponent::Init()
{
	Marker.Empty();
	TArray<AActor*> marked;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMarked::StaticClass(), marked);
	for (int i = 0; i < marked.Num(); i++)
	{
		UMarkerComponent* marker = IMarked::Execute_GetMarker(marked[i]);
		Marker.Add(marker);
	}
}
