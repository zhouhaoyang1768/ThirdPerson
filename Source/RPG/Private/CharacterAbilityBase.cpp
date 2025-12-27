// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilityBase.h"
#include "RPGCharacter.h"

void UCharacterAbilityBase::Initialize_Implementation(class ACharacterBase* InOwnerCharacter)
{
	this->OwnerCharacter = InOwnerCharacter;
}

bool UCharacterAbilityBase::CanActivate()
{
	FGameplayTagContainer OwnerGameplayTags;
	check(OwnerCharacter.IsValid());
	OwnerCharacter->GetOwnedGameplayTags(OwnerGameplayTags);
	return !OwnerGameplayTags.HasAny(ActivationBlockedTags) && CoolDownCounter == 0;
}

bool UCharacterAbilityBase::CanInterrput(float InterruptIntensity)
{
	return InterruptIntensity > AntiInterruptability;
}

void UCharacterAbilityBase::Activate()
{
	TRACE_CPUPROFILER_EVENT_SCOPE_STR("Ability Activate");
	check(OwnerCharacter.IsValid());
	OwnerCharacter->AddGameplayTagToCharacter(AbilityTag);
	CoolDownCounter = CoolDown;
	OnAbilityActivated.Broadcast(AbilityTag, this);
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

void UCharacterAbilityBase::CoolDownTick(float dt)
{
	CoolDownCounter -= dt;
	if (CoolDownCounter < 0) CoolDownCounter = 0;
}