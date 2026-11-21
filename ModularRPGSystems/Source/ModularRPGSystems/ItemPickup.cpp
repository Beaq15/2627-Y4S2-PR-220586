// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "ItemDefinition.h"
#include "InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(80.f);
	Sphere->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AItemPickup::OnSphereBeginOverlap);
}

void AItemPickup::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !Definition) return;

	UInventoryComponent* Inventory = OtherActor->FindComponentByClass<UInventoryComponent>();
	if (!Inventory) return;

	const int32 Added = Inventory->AddItem(Definition, Count);
	Count -= Added;

	if (Count <= 0)
		Destroy();
}

