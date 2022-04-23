#pragma once
#include "CoreMinimal.h"
#include "Human.h"
#include "Avatar.generated.h"

UCLASS()
class LNR_API AAvatar : public ACharacter
{
	GENERATED_BODY()
public:
	AAvatar();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UApparelComponent* Apparel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAvatarComponent* Avatar;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* TpArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* TpCamera;
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Zoom(float val);
};
