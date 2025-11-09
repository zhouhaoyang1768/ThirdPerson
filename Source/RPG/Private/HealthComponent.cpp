// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ImmuneTime > 0)
	{
		ImmuneTime -= DeltaTime;
		if (ImmuneTime < 0) ImmuneTime = 0;
	}
}


void UHealthComponent::TakeDamage(float Damage)
{
	if (Damage > 0 && ImmuneTime != 0)
	{
		return;
	}
	CurrentHP -= Damage;
	if (CurrentHP < 0) CurrentHP = 0;
	if (CurrentHP > MaxHP) CurrentHP = MaxHP;
}

void UHealthComponent::Heal(float Amount)
{
	if (Amount < 0 && ImmuneTime != 0)
	{
		return;
	}
	CurrentHP += Amount;
	if (CurrentHP < 0) CurrentHP = 0;
	if (CurrentHP > MaxHP) CurrentHP = MaxHP;

}

void UHealthComponent::SetImmuneTime(float Duration)
{
	ImmuneTime = Duration;
}


bool UHealthComponent::IsImmune()
{
	return ImmuneTime != 0;
}