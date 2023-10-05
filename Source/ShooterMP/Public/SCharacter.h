#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;

UCLASS()
class SHOOTERMP_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<AActor> ProjectileClass;

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;
	
	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryAttack();
	void PrimaryInteraction();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void DrawDebugArrows();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
