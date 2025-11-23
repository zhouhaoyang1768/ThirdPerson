// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "CharacterBase.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//WeaponCapsuleTransform = new FTransform(FRotator(0, 0, 0), FVector(0, 0, 50), FVector(1.0, 1.0, 1.0));
	//WeaponMeshTransform = FTransform(FRotator(0, -90, 0), FVector(-5, 0, 50), FVector(0.3, 0.3, 0.3));

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();


	FName RightHand = FName(TEXT("HandGrip_R"));
	FTransform Transform;

	//AttachWeaponMeshTo(RightHand, WeaponMeshTransform);
	//AttachWeaponCapsuleTo(RightHand, WeaponCapsuleTransform);
	DisableHitbox();
	ShowWeapon();
	// ...

}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UWeaponComponent::AttachWeaponMeshTo(FName Socket, const FTransform& Transform)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	if (ACharacterBase* Character = Cast<ACharacterBase>(GetOwner()))
	{
		Character->WeaponMesh->AttachToComponent(Character->GetMesh(), TransformRules, Socket);
		Character->WeaponMesh->SetRelativeTransform(Transform);
	}
}


void UWeaponComponent::AttachWeaponCapsuleTo(FName Socket, const FTransform& Transform)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

	if (ACharacterBase* Character = Cast<ACharacterBase>(GetOwner()))
	{
		bool ok = Character->WeaponCapsule->AttachToComponent(Character->GetMesh(), TransformRules, Socket);

		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, ok ? "ok" : "not ok");
		Character->WeaponCapsule->SetRelativeTransform(Transform);
	}
}


void UWeaponComponent::EnableHitbox()
{
	if (ACharacterBase* Character = Cast<ACharacterBase>(GetOwner()))
	{
		Character->WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	}
}



void UWeaponComponent::DisableHitbox()
{
	if (ACharacterBase* Character = Cast<ACharacterBase>(GetOwner()))
	{
		Character->WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
}



void UWeaponComponent::ShowWeapon()
{
	if (ACharacterBase* Character = Cast<ACharacterBase>(GetOwner()))
	{
		Character->WeaponMesh->SetHiddenInGame(false);
	}
}



void UWeaponComponent::HideWeapon()
{
	if (ACharacterBase* Character = Cast<ACharacterBase>(GetOwner()))
	{
		Character->WeaponMesh->SetHiddenInGame(true);
	}
}