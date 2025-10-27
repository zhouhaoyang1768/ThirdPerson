// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAbilityBase.h"
#include "GameplayTagContainer.h"


#include "AbilityManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityManagerComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<TSubclassOf<class UCharacterAbilityBase>> InitialEquippedAbilities;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Ability")
	TMap<FGameplayTag, TObjectPtr<UCharacterAbilityBase>> EquippedAbilitiesMap;
public:		

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool TryActivateAvilityWithTag(const FGameplayTag& AbilityGameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool TryDeactivateAvilityWithTag(const FGameplayTag& AbilityGameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool CanMove();

};
