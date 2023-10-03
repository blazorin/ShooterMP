// Alberto Romero


#include "SExplosionBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosionBarrel::ASExplosionBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = SceneComp;

	// Barrel Mesh
	BarrelComp = CreateDefaultSubobject<UStaticMeshComponent>("BarrelComp");
	BarrelComp->SetupAttachment(SceneComp);

	BarrelComp->SetSimulatePhysics(true);
	//BarrelComp->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	
	// Barrel Force
	BarrelForceComp = CreateDefaultSubobject<URadialForceComponent>("BarrelForceComp");
	BarrelForceComp->SetupAttachment(BarrelComp);

	BarrelForceComp->SetAutoActivate(false);
	
	BarrelForceComp->Radius = 750.0f;
	BarrelForceComp->ImpulseStrength = 1200.0f;
	
	// Optional, ignores 'Mass' of other objects
	BarrelForceComp->bImpulseVelChange = true;

	//BarrelForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void ASExplosionBarrel::OnBarrelHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetRootComponent()->GetCollisionObjectType() != ECollisionChannel::ECC_WorldDynamic)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Barrel Hit from WorldDynamic"));
	BarrelForceComp->FireImpulse();
	
	/*const FString actorName = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *actorName);*/
}

// Called when the game starts or when spawned
void ASExplosionBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosionBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BarrelComp->OnComponentHit.AddDynamic(this, &ASExplosionBarrel::OnBarrelHit);
}

// Called every frame
void ASExplosionBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



