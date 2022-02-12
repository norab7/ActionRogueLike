// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"

#include "SAttributeComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Base Mesh
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	// Attribute Component
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");

	// Bindings
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);

}

// Called when the game starts or when spawned
void ASTargetDummy::BeginPlay() {
	Super::BeginPlay();

}

void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta) {
	if (Delta < 0.f) {
		BaseMesh->SetScalarParameterValueOnMaterials(TEXT("TimeToHit"), GetWorld()->TimeSeconds);
	}
}

// Called every frame
void ASTargetDummy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

