#include "Consumable.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"
// #include "LNR/Component/InventoryComponent.h"

void UConsumable::UseItem(AHero* nHero, int amount)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, "Consumable Use Item not Implemented!");
	// if (nHero != nullptr)
	// {
	// 	nHero->Equipment->EquipConsumable(this, amount);
	// 	nHero->Inventory->RemoveItem(this, amount);
	// }
}

FString UConsumable::PrintItemData(bool withDescription)
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Consumable\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if (withDescription) data += "Description: " + Description + "\r";
	return data;
}

void UConsumable::Consume_Implementation(ABody* nBody)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, "Consume Implementation!");
}

void UConsumable::UseConsumable(ABody* nBody)
{
	Body = nBody;
	if (Body->HasAuthority())
	{
		Body->Combat->State = Reacting;
		nBody->MultiPlayMontage(Montage);
		PlayMontage(Body, Montage);
	}
	else ServerUseConsumable(Body);
}

void UConsumable::PlayMontage(ABody* nBody, UAnimMontage* nMontage)
{
	UAnimInstance* AnimInstance = nBody->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(nMontage);
	AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UConsumable::OnNotifyBegin);
	FOnMontageEnded BlendOutDelegate;
	BlendOutDelegate.BindUObject(this, &UConsumable::OnAnimationBlendOut);
	AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, nMontage);
}

void UConsumable::OnNotifyBegin(FName nName, const FBranchingPointNotifyPayload& payload)
{
	payload.SkelMeshComponent->GetAnimInstance()->OnPlayMontageNotifyBegin.Clear();
	Consume(Body);
}

void UConsumable::OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	if (Body->Combat->State == Dead) return;
	else
	{
		Body->Combat->State = Idle;
		if (Body->BlockPressed) Body->Block();
	}
}
