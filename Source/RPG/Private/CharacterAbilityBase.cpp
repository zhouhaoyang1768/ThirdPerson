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

bool UCharacterAbilityBase::CanInterrput(float InterruptIntensity)
{
	return InterruptIntensity > AntiInterruptability;
}

void UCharacterAbilityBase::Activate()
{
	check(OwnerCharacter.IsValid());
	OwnerCharacter->AddGameplayTagToCharacter(AbilityTag);
	OnAbilityActivated.Broadcast(AbilityTag, this);

	// OwnerCharacter->GetWorld()->SpawnActor();
}

void UCharacterAbilityBase::Interrupt()
{
	check(OwnerCharacter.IsValid());
	OnAbilityInterrputed.Broadcast(AbilityTag, this);
	OwnerCharacter->RemoveGameplayTagFromCharacter(AbilityTag);
}

void UCharacterAbilityBase::Deactivate()
{
	check(OwnerCharacter.IsValid());
	OnAbilityDeactivated.Broadcast(AbilityTag, this);
	OwnerCharacter->RemoveGameplayTagFromCharacter(AbilityTag);
}