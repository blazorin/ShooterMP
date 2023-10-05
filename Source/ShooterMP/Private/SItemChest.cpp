// Alberto Romero


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMeshComp");
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("LidMeshComp");
	LidMeshComp->SetupAttachment(BaseMeshComp);

	TargetPitch = 105;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("A chest has open!"));
	LidMeshComp->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

