#include "CombatComponent.h"
#include "AttributesComponent.h"
#include "EquipmentComponent.h"
#include "HeadSphereComponent.h"
#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Humanoid.h"
#include "LNR/DamageType/MeleeDamage.h"
#include "LNR/DamageType/RangedDamage.h"
#include "LNR/Item/Weapon.h"
#include "Net/UnrealNetwork.h"

UCombatComponent::UCombatComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	State = Idle;
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCombatComponent, Combo);
	DOREPLIFETIME(UCombatComponent, MeleeHits);
	DOREPLIFETIME(UCombatComponent, Aiming);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatComponent, State, COND_None, REPNOTIFY_Always);
}

void UCombatComponent::OnRep_State(EState nState)
{
	RefreshState();
}

void UCombatComponent::Setup(ABody* nBody)
{
	Body = nBody;
	Humanoid = Cast<AHumanoid>(Body);
}

void UCombatComponent::RefreshState()
{
	// if(State == Dead) Body->Die();
	// Print(State);
}

UAnimMontage* UCombatComponent::GetCombatMontage()
{
	if (Humanoid && Humanoid->Equipment->GetWeapon(0) != nullptr)
	{
		UWeapon* w = Humanoid->Equipment->GetWeapon(0);
		return w->CombatMontage[Combo];
	}
	else return UnarmedMontage[Combo];
}

int UCombatComponent::GetMaxCombo()
{
	if (Humanoid && Humanoid->Equipment->GetWeapon(0) != nullptr)
	{
		return Humanoid->Equipment->GetWeapon(0)->CombatMontage.Num();
	}
	else return UnarmedMontage.Num();
}

void UCombatComponent::ResetCombo()
{
	GetWorld()->GetTimerManager().ClearTimer(ResetComboHandle);
	Combo = 0;
}

void UCombatComponent::TraceMelee()
{
	FVector start = Body->GetMesh()->GetSocketLocation("Melee");
	FHitResult hit;
	TArray<AActor*> toIgnore;
	toIgnore.Add(GetOwner());
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), start, start, MeleeRange, TraceTypeQuery1, true,
	                                            toIgnore, EDrawDebugTrace::ForDuration, hit, true,
	                                            FLinearColor::Red, FLinearColor::Green, 1))
	{
		if (AActor* hitActor = hit.GetActor())
		{
			if (!MeleeHits.Contains(hitActor))
			{
				MeleeHits.Add(hitActor);
				UGameplayStatics::ApplyPointDamage(hitActor, Body->Attributes->Damage, Body->GetActorLocation(), hit,
				                                   Body->GetController(), Body, UMeleeDamage::StaticClass());
			}
		}
	}
}

void UCombatComponent::TraceMeleeSockets(TArray<FName> sockets, int radius)
{
	for (const FName name : sockets)
	{
		FVector start = Body->GetMesh()->GetSocketLocation(name);
		FHitResult hit;
		TArray<AActor*> toIgnore;
		toIgnore.Add(GetOwner());
		if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), start, start, radius, TraceTypeQuery1, true,
		                                            toIgnore, EDrawDebugTrace::ForDuration, hit, true,
		                                            FLinearColor::Red, FLinearColor::Green, 1))
		{
			if (AActor* hitActor = hit.GetActor())
			{
				if (!MeleeHits.Contains(hitActor))
				{
					MeleeHits.Add(hitActor);
					UGameplayStatics::ApplyPointDamage(hitActor, Body->Attributes->Damage, Body->GetActorLocation(),
					                                   hit, Body->GetController(), Body, UMeleeDamage::StaticClass());
				}
			}
		}
	}
}

void UCombatComponent::TraceWeapon(UWeaponComponent* weapon)
{
	FVector start = weapon->GetSocketLocation("TraceStart");
	FVector end = weapon->GetSocketLocation("TraceFinish");
	FHitResult hit;
	TArray<AActor*> toIgnore;
	toIgnore.Add(GetOwner());
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), start, end, 20, TraceTypeQuery1, true,
	                                            toIgnore, EDrawDebugTrace::ForDuration, hit, true,
	                                            FLinearColor::Red, FLinearColor::Green, 1))
	{
		if (AActor* hitActor = hit.GetActor())
		{
			if (!MeleeHits.Contains(hitActor))
			{
				MeleeHits.Add(hitActor);
				UGameplayStatics::ApplyPointDamage(hitActor, Body->Attributes->Damage, Body->GetActorLocation(), hit,
				                                   Body->GetController(), Body, UMeleeDamage::StaticClass());
			}
		}
	}
}

void UCombatComponent::Shoot()
{
	if (AController* controller = Body->GetController())
	{
		FVector start;
		FRotator rot;
		controller->GetPlayerViewPoint(start, rot);
		FVector end = start + (rot.Vector() * 5000.0f);
		FHitResult hit;
		TArray<AActor*> toIgnore;
		toIgnore.Add(GetOwner());
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, TraceTypeQuery1, true,
		                                          toIgnore, EDrawDebugTrace::ForDuration, hit, true,
		                                          FLinearColor::Red, FLinearColor::Green, 1))
		{
			if (AActor* hitActor = hit.GetActor())
			{
				TSubclassOf<UDamageType> dt = URangedDamage::StaticClass();
				int dmg = Body->Attributes->Damage;
				if (Cast<UHeadSphereComponent>(hit.GetComponent()))
				{
					dt = UMeleeDamage::StaticClass();
					dmg *= 2;
				}
				UGameplayStatics::ApplyPointDamage(hitActor, dmg, Body->GetActorLocation(), hit,
				                                   Body->GetController(), Body, dt);
			}
		}
	}
}

void UCombatComponent::SetState(EState nState)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		State = nState;
		RefreshState();
	}
	else ServerSetState(nState);
}

void UCombatComponent::SetAiming(bool val)
{
	if (GetOwnerRole() == ROLE_Authority) Aiming = val;
	else ServerSetAiming(val);
}
