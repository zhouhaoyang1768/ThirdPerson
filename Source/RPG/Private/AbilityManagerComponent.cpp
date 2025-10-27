// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityManagerComponent.h"
#include "CharacterAbilityBase.h"
#include "RPGCharacter.h"
#include "GameplayTagContainer.h"

UAbilityManagerComponent::UAbilityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	for (TSubclassOf<UCharacterAbilityBase>& AbilityClass : InitialEquippedAbilities)
	{
		UCharacterAbilityBase* CharacterAbility = NewObject<UCharacterAbilityBase>(this, AbilityClass.Get(), FName(*AbilityClass->GetName()));
		CharacterAbility->Initialize(Cast<ARPGCharacter>(GetOwner()));
		EquippedAbilitiesMap.Add(CharacterAbility->GetAbilityGameplayTag(), CharacterAbility);
	}
	
}



bool UAbilityManagerComponent::TryActivateAvilityWithTag(const FGameplayTag& AbilityGameplayTag)
{
	if (TObjectPtr<UCharacterAbilityBase>* CharacterAbility = EquippedAbilitiesMap.Find(AbilityGameplayTag))
	{
		if ((*CharacterAbility)->CanActivate())
		{
			(*CharacterAbility)->Activate();
			return true;
		}
	}
	return false;
}


bool UAbilityManagerComponent::TryDeactivateAvilityWithTag(const FGameplayTag& AbilityGameplayTag)
{
	if (TObjectPtr<UCharacterAbilityBase>* CharacterAbility = EquippedAbilitiesMap.Find(AbilityGameplayTag))
	{
		(*CharacterAbility)->Deactivate();
		return true;
	}
	return false;
}

bool UAbilityManagerComponent::CanMove()
{
	/*FGameplayTagContainer OwnerGameplayTags;

	if (ARPGCharacter* character = Cast<ARPGCharacter>(GetOwner()))
	{
		character->GetOwnedGameplayTags(OwnerGameplayTags);
		return OwnerGameplayTags.IsEmpty();
	}*/
	return true;
}