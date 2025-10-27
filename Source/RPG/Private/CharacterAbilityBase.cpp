// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilityBase.h"
#include "RPGCharacter.h"

void UCharacterAbilityBase::Initialize_Implementation(class ARPGCharacter* InOwnerCharacter)
{
	this->OwnerCharacter = InOwnerCharacter;
}

bool UCharacterAbilityBase::CanActivate()
{
	FGameplayTagContainer OwnerGameplayTags;
	check(OwnerCharacter.IsValid());
	OwnerCharacter->GetOwnedGameplayTags(OwnerGameplayTags);
	return !OwnerGameplayTags.HasAny(ActivationBlockedTags);
}

void UCharacterAbilityBase::Activate()
{
	check(OwnerCharacter.IsValid());
	OwnerCharacter->AddGameplayTagToCharacter(AbilityTag);
	OnAbilityActivated.Broadcast(AbilityTag, this);
}

void UCharacterAbilityBase::Deactivate()
{
	check(OwnerCharacter.IsValid());
	OnAbilityDeactivated.Broadcast(AbilityTag, this);
	OwnerCharacter->RemoveGameplayTagFromCharacter(AbilityTag);
}