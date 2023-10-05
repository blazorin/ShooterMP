// Alberto Romero

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOOTERMP_API ISGameplayInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
	
};
