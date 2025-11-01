// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"


#include "CharacterAbilityBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAbilityActivationEvent, const FGameplayTag&, AvilityGameplayTag, const UCharacterAbilityBase*, AbilityPtr);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class RPG_API UCharacterAbilityBase : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void Initialize(class ARPGCharacter* InOwnerCharacter);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual bool CanActivate();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual bool CanInterrput(float InterruptIntensity);
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void Activate();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void Interrupt();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void Deactivate();


	UFUNCTION(BlueprintCallable, Category = "Ability")
	const FGameplayTag GetAbilityGameplayTag() { return AbilityTag; }

	UPROPERTY(BlueprintAssignable)
	FAbilityActivationEvent OnAbilityActivated;

	UPROPERTY(BlueprintAssignable)
	FAbilityActivationEvent OnAbilityInterrputed;


	UPROPERTY(BlueprintAssignable)
	FAbilityActivationEvent OnAbilityDeactivated;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (Categories = "Character.Ability"))
	float AntiInterruptability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (Categories = "Character.Ability")) 
	FGameplayTag AbilityTag;

	// if we are activated then stop these abilities from being activated
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (Categories = "Character.Ability"))
	FGameplayTagContainer BlockAbilitiesWithTag;

	// if these tags are activated then we can't be activated
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (Categories = "Character.Ability"))
	FGameplayTagContainer ActivationBlockedTags;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<class ARPGCharacter> OwnerCharacter = nullptr;
};
