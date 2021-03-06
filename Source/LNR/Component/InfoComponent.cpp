#include "InfoComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UInfoComponent::UInfoComponent()
{
	SetTwoSided(true);
	SetVisibility(true);
	SetDrawAtDesiredSize(false);
	SetDrawSize(FVector2D(100, 30));
	SetWorldRotation(FRotator(0, 0, 0));
	SetTickMode(ETickMode::Automatic);
	SetWidgetSpace(EWidgetSpace::World);
}

void UInfoComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UInfoComponent::Init()
{
	if (UUserWidget* widget = GetWidget())
	{
		InfoWidget = Cast<UInfoWidget>(widget);
		if (InfoWidget)
		{
			InfoWidget->Info = this;
			InfoWidget->Refresh();
		}
	}
	ClearTimer();
}

void UInfoComponent::Init(UAttributesComponent* nAttributes)
{
	if (UUserWidget* widget = GetWidget())
	{
		InfoWidget = Cast<UInfoWidget>(widget);
		if (InfoWidget)
		{
			InfoWidget->Info = this;
			InfoWidget->Attributes = nAttributes;
			InfoWidget->Refresh();
		}
	}
	ClearTimer();
}

void UInfoComponent::Show(bool val)
{
	if (!HideInfoTimerActive) SetVisibility(val);
}

void UInfoComponent::StartTimer(float time)
{
	ClearTimer();
	Show(true);
	HideInfoTimerActive = true;
	GetWorld()->GetTimerManager().SetTimer(HideInfoTimer, this, &UInfoComponent::ClearTimer, time);
}

void UInfoComponent::ClearTimer()
{
	HideInfoTimerActive = false;
	Show(false);
	GetWorld()->GetTimerManager().ClearTimer(HideInfoTimer);
}

void UInfoComponent::Setup(ACharacter* character)
{
	if (UCapsuleComponent* nCapsule = character->GetCapsuleComponent())
	{
		AttachToComponent(nCapsule, FAttachmentTransformRules::KeepWorldTransform);
		SetRelativeLocation(FVector(0, 0, nCapsule->Bounds.BoxExtent.Z + 30));
	}
	else SetRelativeLocation(FVector(0, 0, 120));
}
