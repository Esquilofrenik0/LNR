#include "Consumable.h"

#include "LNR/Body/Hero.h"
#include "LNR/Component/EquipmentComponent.h"
// #include "LNR/Component/InventoryComponent.h"
// #include "LNR/Component/MantlingComponent.h"

void UConsumable::UseItem(AHero* nHero, int amount)
{
	Print("Consumable Use Item Not Implemented!");
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
	Print("Consume_Implementation");
}

void UConsumable::UseConsumable(ABody* nBody)
{
	Print("Consumable Use Consumable Not Implemented!");
	// Body = nBody;
	// if (Body->HasAuthority())
	// {
	// 	Body->State = Reacting;
	// 	USkeletalMeshComponent* nMesh = Body->GetMesh();
	// 	nBody->MultiPlayMontage(nMesh, Montage);
	// 	PlayMontage(Body, nMesh, Montage);
	// }
	// else ServerUseConsumable(Body);
}

void UConsumable::PlayMontage(ABody* nBody, USkeletalMeshComponent* nMesh, UAnimMontage* nMontage)
{
	UAnimInstance* AnimInstance = nMesh->GetAnimInstance();
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
	Print("Consumable OnAnimationBlendOut Not Implemented!");	
	// if(Body->State == Dead) return;
	// else
	// {
	// 	Body->State = Idle;
	// 	if(Body->IsBlocking) Body->Block();
	// }
}