
#include "SCharacter.h"

#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugArrows();
}



void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(PrimaryAttackAnim);

	GetWorld()->GetTimerManager().SetTimer(PrimaryAttackTimerHandle, this, &ASCharacter::PrimaryAttack_Timer, 0.2f);
}

void ASCharacter::PrimaryAttack_Timer()
{
	// Get hand muzzle location
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	const FTransform SpawnTF = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTF, SpawnParams);
	
	//FVector RightVector = GetActorRightVector();

	// Log the right vector to the console
	//UE_LOG(LogTemp, Warning, TEXT("Actor's Right Vector: X = %f, Y = %f, Z = %f"), RightVector.X, RightVector.Y, RightVector.Z);
}


void ASCharacter::PrimaryInteraction()
{
	InteractionComp->PrimaryInteraction();
}



// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward); // W - S
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight); // A - D
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); // Mouse X (Y)
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput); // Mouse Y (X)

	// Actions
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteraction", IE_Pressed, this, &ASCharacter::PrimaryInteraction);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	
}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	
	AddMovementInput(ControlRotation.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, value);
}


void ASCharacter::DrawDebugArrows()
{
	// Rotation Visualization
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f; // same as FVector(0, 100.0f, 0) (directional vector)
	// Set line end in direction of the actor's forward
	const FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	const FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

