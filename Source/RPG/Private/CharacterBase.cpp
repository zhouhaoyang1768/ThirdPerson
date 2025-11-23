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
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	FAttachmentTransformRules WeaponCapsuleTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	FName RightHand = FName(TEXT("HandGrip_R"));

	WeaponCapsule->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 50), FVector(0.3, 0.3, 1.0)));
	WeaponCapsule->SetupAttachment(GetMesh(), RightHand);
	WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);


	WeaponMesh->SetupAttachment(GetMesh(), RightHand);
	WeaponMesh->SetRelativeTransform(FTransform(FRotator(-90, 0, 0), FVector(-5, 0, 50), FVector(0.3, 0.3, 0.3)));
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
	switch (AttackEventType)
	{
	case EAttackEventType::ATTACH_LEFT_HAND:
		//WeaponComponent->AttachWeaponCapsuleTo(FName(TEXT("HandGrip_L")), FTransform(FQuat(FVector::XAxisVector, 90)));
		WeaponComponent->EnableHitbox();
		//WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		break;

	case EAttackEventType::ATTACH_RIGHT_HAND:
		//WeaponComponent->AttachWeaponCapsuleTo(FName(TEXT("HandGrip_R")), FTransform(FQuat(FVector::XAxisVector, 90)));
		WeaponComponent->EnableHitbox();
		//WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		break;

	case EAttackEventType::ATTACH_RIGHT_FOOT:
		//WeaponComponent->AttachWeaponCapsuleTo(FName(TEXT("foot_r_Socket")), FTransform(FQuat(FVector::ZAxisVector, 90)));
		WeaponComponent->EnableHitbox();
		//WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		break;

	case EAttackEventType::DETACH:
		WeaponComponent->DisableHitbox();
		//WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		break;
	default:
		WeaponComponent->DisableHitbox();
		//WeaponCapsule->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		break;
	}
}

void ACharacterBase::HandleDamage(const AActor* Source, float Damage, float InterruptIntensity)
{
	OnTakeDamage.Broadcast(Source, Damage, InterruptIntensity);
}