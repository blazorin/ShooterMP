// Alberto Romero


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USInteractionComponent::PrimaryInteraction()
{
	AActor* OwnerActor = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	
	OwnerActor->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector EyeRotationVector = EyeRotation.Vector();
	FVector EndLocation = EyeLocation + (EyeRotationVector * 250.0f);
	//UE_LOG(LogTemp, Warning, TEXT("EyeRotation Vector: X = %f, Y = %f, Z = %f"), EyeRotationVector.X, EyeRotationVector.Y, EyeRotationVector.Z);

	
	FCollisionObjectQueryParams CollisionQuery;
	CollisionQuery.AddObjectTypesToQuery(ECC_WorldDynamic);
	CollisionQuery.AddObjectTypesToQuery(ECC_WorldStatic);
	
	//FHitResult HitResult;
	//GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, EndLocation, CollisionQuery);

	constexpr float Radius = 35.0f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	TArray<FHitResult> HitResults;
	const bool bHitObject = GetWorld()->SweepMultiByObjectType(HitResults, EyeLocation, EndLocation, FQuat::Identity, CollisionQuery, Shape);

	
	for (const FHitResult& HitResult : HitResults)
	{
		// Check if we hit an Object inheriting GameplayInterface
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (!HitActor->Implements<USGameplayInterface>())
				break;
		
			ISGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(OwnerActor));
		}

		DrawDebugSphere(GetWorld(), HitResult.Location, Radius, 32, (bHitObject ? FColor::Red : FColor::Emerald), false, 1.5f);
		break;
	}

	// Debug
	DrawDebugLine(GetWorld(), EyeLocation, EndLocation, (bHitObject ? FColor::Red : FColor::Emerald), false, 1.5f, 0, 3.0f);
}


