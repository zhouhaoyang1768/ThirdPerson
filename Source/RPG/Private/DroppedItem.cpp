// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedItem.h"

// Sets default values
ADroppedItem::ADroppedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Range"));

	Collision->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
	Collision->SetCollisionProfileName(TEXT("BlockAll"));

	PickupRange->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(4.0, 4.0, 4.0)));
	PickupRange->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);


	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
//	ProjectileMovement
	Collision->SetupAttachment(Scene);
	PickupRange->SetupAttachment(Collision);
	Mesh->SetupAttachment(Collision);

	Collision->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADroppedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADroppedItem::Create(UItemBase* _Item)
{
	this->Item = _Item;
	this->Mesh->SetStaticMesh(Item->GetMesh());
}

void ADroppedItem::PickUp(ACharacterBase* Character)
{
	this->Destroy();
}