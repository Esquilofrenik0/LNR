#include "NavigationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Interface/Marked.h"

UNavigationComponent::UNavigationComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	Discovered.Empty();
	Discovered.Add("Marker");
	Discovered.Add("Genesis");
	Discovered.Add("Container");
	Discovered.Add("Distos");
	Discovered.Add("Gaea");
	Discovered.Add("Meat");
	Discovered.Add("Ministerium");
	Discovered.Add("Port");
	Discovered.Add("Station");
	Discovered.Add("Utopy");
	Discovered.Add("Airport");
	Discovered.Add("Tekan00");
	Discovered.Add("Tekan01");
	Discovered.Add("Tekan02");
	Discovered.Add("Tekan10");
	Discovered.Add("Tekan11");
	Discovered.Add("Tekan12");
	Discovered.Add("Tekan20");
	Discovered.Add("Tekan21");
	Discovered.Add("Tekan22");
}

void UNavigationComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().ClearTimer(InitHandle);
	GetWorld()->GetTimerManager().SetTimer(InitHandle, this, &UNavigationComponent::Init, 2, false);
}

void UNavigationComponent::Init()
{
	GetWorld()->GetTimerManager().ClearTimer(InitHandle);
	Marker.Empty();
	TArray<AActor*> marked;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMarked::StaticClass(), marked);
	for (int i = 0; i < marked.Num(); i++)
	{
		UMarkerComponent* marker = IMarked::Execute_GetMarker(marked[i]);
		Marker.Add(marker);
	}
}
