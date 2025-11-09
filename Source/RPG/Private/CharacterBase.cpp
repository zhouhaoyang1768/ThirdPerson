// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AbilityManagerComponent = CreateDefaultSubobject<UAbilityManagerComponent>(TEXT("AbilityManager"));
	HitReactComponent = CreateDefaultSubobject<UHitReactComponent>(TEXT("HitReact"));
	WeaponCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCapsule"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	// FAttachmentTransformRules WeaponCapsuleTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	FName RightHand = FName(TEXT("ik_hand_r"));
	FQuat Rotation(FVector::YAxisVector, 90);
	WeaponCapsule->SetRelativeRotation(Rotation);
	WeaponCapsule->SetupAttachment(GetMesh(), RightHand);
	WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ACharacterBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const {
	TagContainer = OwnedGameplayTags;
}
void ACharacterBase::AddGameplayTagToCharacter(FGameplayTag& GameplayTagToAdd) {
	OwnedGameplayTags.AddTag(GameplayTagToAdd);
}
void ACharacterBase::RemoveGameplayTagFromCharacter(FGameplayTag& GameplayTagToRemove) {
	OwnedGameplayTags.RemoveTag(GameplayTagToRemove);
}
void ACharacterBase::AddGameplayTagsToCharacter(FGameplayTagContainer& GameplayTagsToAdd) {
	OwnedGameplayTags.AppendTags(GameplayTagsToAdd);
}
void ACharacterBase::RemoveGameplayTagsFromCharacter(FGameplayTagContainer& GameplayTagsToRemove) {
	OwnedGameplayTags.RemoveTags(GameplayTagsToRemove);
}

void ACharacterBase::HandleAnimNotify(EAttackEventType AttackEventType)
{

	FAttachmentTransformRules WeaponCapsuleTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

	FName LeftHand = FName(TEXT("ik_hand_l"));
	FName RightHand = FName(TEXT("ik_hand_r"));
	FName RightFoot = FName(TEXT("ik_foot_r"));

	switch (AttackEventType)
	{
	case EAttackEventType::ATTACH_LEFT_HAND:
		WeaponCapsule->AttachToComponent(GetMesh(), WeaponCapsuleTransformRules, LeftHand);
		//WeaponCapsule->Activate();
		WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		break;

	case EAttackEventType::ATTACH_RIGHT_HAND:
		WeaponCapsule->AttachToComponent(GetMesh(), WeaponCapsuleTransformRules, RightHand);
		//WeaponCapsule->Activate();
		WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		break;

	case EAttackEventType::ATTACH_RIGHT_FOOT:
		WeaponCapsule->AttachToComponent(GetMesh(), WeaponCapsuleTransformRules, RightFoot);
		//WeaponCapsule->Activate();
		WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		break;
	case EAttackEventType::DETACH:
		//WeaponCapsule->Deactivate();
		WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		break;
	default:
		//WeaponCapsule->Deactivate();
		WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		break;
	}
}

void ACharacterBase::HandleDamage(const AActor* Source, float Damage, float InterruptIntensity)
{
	OnTakeDamage.Broadcast(Source, Damage, InterruptIntensity);
}