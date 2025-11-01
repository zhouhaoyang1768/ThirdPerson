// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExplosionBase.h"
#include "GameFramework/Character.h"
#include "CombatAttacker.h"
#include "AbilityManagerComponent.h"
#include "HitReactComponent.h"
#include "HitReactComponent.h"
#include "Logging/LogMacros.h"
#include "GameplayTagAssetInterface.h"

#include "RPGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ARPGCharacter : public ACharacter, public ICombatAttacker, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAbilityManagerComponent> AbilityManagerComponent = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHitReactComponent> HitReactComponent = nullptr;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Master Ability Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MasterAbilityAction;

	/** explosion class to spawn */
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AExplosionBase> ExplosionClass = nullptr;


	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AExplosionBase> NormalAttackClass = nullptr;

public:

	/** Constructor */
	ARPGCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


	void StartMasterAbility(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:


	void DoAttackTrace(FName DamageSourceBone) override;

	void CheckCombo() override;

	void CheckChargedAttack() override;

	void DoAOEAttack() override;

	void DoNormalAttack() override;

	//UFUNCTION(BlueprintCallable)
	//void SpawnActor(TObjectPtr<AActor> actor);

public:
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override {
		TagContainer = OwnedGameplayTags;
	}
	virtual void AddGameplayTagToCharacter(FGameplayTag& GameplayTagToAdd) {
		OwnedGameplayTags.AddTag(GameplayTagToAdd);
	}
	virtual void RemoveGameplayTagFromCharacter(FGameplayTag& GameplayTagToRemove) {
		OwnedGameplayTags.RemoveTag(GameplayTagToRemove);
	}
	virtual void AddGameplayTagsToCharacter(FGameplayTagContainer& GameplayTagsToAdd) {
		OwnedGameplayTags.AppendTags(GameplayTagsToAdd);
	}
	virtual void RemoveGameplayTagsFromCharacter(FGameplayTagContainer& GameplayTagsToRemove) {
		OwnedGameplayTags.RemoveTags(GameplayTagsToRemove);
	}


protected:
	UPROPERTY(VisibleAnywhere)
	FGameplayTagContainer OwnedGameplayTags;
};

