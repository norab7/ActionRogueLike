// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASCharacter::ASCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	PrimaryAttackDelay = 0.2f;
	HitFlashColor = FColor::White;
	HitFlashSpeed = 2.f;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay() {
	Super::BeginPlay();
}

void ASCharacter::MoveForward(float Value) {
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	AddMovementInput(ControlRot.Vector() * Value);
}

void ASCharacter::MoveRight(float Value) {
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	// X - Forward - Red
	// Y - Right - Green
	// Z - Up - Blue

	const FVector ControlRightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(ControlRightVector * Value);
}

void ASCharacter::PrimaryAttack() {
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttackTimeElapsed, PrimaryAttackDelay);
}

void ASCharacter::PrimaryAttackTimeElapsed() {
	SpawnProjectile(ProjectileClass);
}

void ASCharacter::BlackholeAttackTimeElapsed() {
	SpawnProjectile(BlackholeClass);
}

void ASCharacter::DashAttackTimeElapsed() {
	SpawnProjectile(DashClass);
}

void ASCharacter::SpawnProjectile(const TSubclassOf<AActor>& Projectile) {

	if (ensure(Projectile)) {

		// Locations
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FVector End = CameraComponent->GetComponentLocation() + (CameraComponent->GetComponentRotation().Vector() * 10000.f);

		// Collision Params
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		// Collision Shape
		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);

		// Sphere Trace
		FHitResult Hit;
		bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit, CameraComponent->GetComponentLocation(), End, FQuat::Identity, ObjectQueryParams, Shape, CollisionQueryParams);

		// Spawn Transform
		FRotator TargetRotation = GetControlRotation();
		if (bBlockingHit) {
			TargetRotation = (Hit.ImpactPoint - HandLocation).Rotation();
		}
		FTransform SpawnTransform = FTransform(TargetRotation, HandLocation);

		// Spawn Params
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;

		// Spawn Projectile
		GetWorld()->SpawnActor<AActor>(Projectile, SpawnTransform, SpawnParameters);
	}

}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta) {
	if (NewHealth <= 0.f && Delta < 0.f) {
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);

	} else {
		if (Delta < 0.f) {
			FVector NormalColor = FVector(HitFlashColor.R, HitFlashColor.G, HitFlashColor.B);
			NormalColor.Normalize();
			GetMesh()->SetVectorParameterValueOnMaterials(TEXT("HitFlashColor"), NormalColor);
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("HitFlashSpeed"), HitFlashSpeed);
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("TimeToHit"), GetWorld()->TimeSeconds);
		}
	}
}

void ASCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

void ASCharacter::PrimaryInteract() {
	if (InteractionComponent) {
		InteractionComponent->PrimaryInteract();
	}
}

void ASCharacter::BlackholeAttack() {
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_BlackholeAttack, this, &ASCharacter::BlackholeAttackTimeElapsed, PrimaryAttackDelay);
}

void ASCharacter::DashAttack() {
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_DashAttack, this, &ASCharacter::DashAttackTimeElapsed, PrimaryAttackDelay);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Action
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("BlackholeAttack", IE_Pressed, this, &ASCharacter::BlackholeAttack);
	PlayerInputComponent->BindAction("DashAttack", IE_Pressed, this, &ASCharacter::DashAttack);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
}

