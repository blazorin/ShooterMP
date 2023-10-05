// Alberto Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosionBarrel.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class SHOOTERMP_API ASExplosionBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosionBarrel();

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrel")
	UStaticMeshComponent* BarrelComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Explosion")
	URadialForceComponent* BarrelForceComp;


	UFUNCTION(Category = "Barrel")
	void OnBarrelHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// To setup dynamic events
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
