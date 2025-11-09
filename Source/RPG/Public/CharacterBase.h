// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "AbilityManagerComponent.h"
#include "Components/CapsuleComponent.h"
#include "HitReactComponent.h"
#include "HealthComponent.h"
#include "GameplayTagAssetInterface.h"
#include "AnimNotifyEnums.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTakeDamageEvent, const AActor*, Source, float, Damage, float, InterruptIntensity);

UCLASS()
class RPG_API ACharacterBase : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


/* ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~  ~~~~ */
public:


	UPROPERTY(BlueprintAssignable)
	FTakeDamageEvent OnTakeDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAbilityManagerComponent> AbilityManagerComponent = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHitReactComponent> HitReactComponent = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCapsuleComponent> WeaponCapsule = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HealthComponent = nullptr;
public:
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual void AddGameplayTagToCharacter(FGameplayTag& GameplayTagToAdd);
	virtual void RemoveGameplayTagFromCharacter(FGameplayTag& GameplayTagToRemove);
	virtual void AddGameplayTagsToCharacter(FGameplayTagContainer& GameplayTagsToAdd);
	virtual void RemoveGameplayTagsFromCharacter(FGameplayTagContainer& GameplayTagsToRemove);

	void HandleAnimNotify(EAttackEventType AttackEventType);

	UFUNCTION(BlueprintCallable)
	void HandleDamage(const AActor* Source, float Damage, float InterruptIntensity);

protected:
	UPROPERTY(VisibleAnywhere)
	FGameplayTagContainer OwnedGameplayTags;
};
