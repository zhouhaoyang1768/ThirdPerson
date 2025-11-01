// Fill out your copyright notice in the Description page of Project Settings.


#include "HitReactComponent.h"
#include "RPGCharacter.h"

// Sets default values for this component's properties
UHitReactComponent::UHitReactComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InterruptIntensity = 0;
	// ...
}


// Called when the game starts
void UHitReactComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitReactComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InterruptIntensity -= DeltaTime * InterruptIntensityRecoveryRate;
	if (InterruptIntensity < 0) InterruptIntensity = 0;
	if (InterruptIntensity > MaxInterruptIntensity) InterruptIntensity = MaxInterruptIntensity;

}

void UHitReactComponent::IncreaseIntensity(float amount)
{
	InterruptIntensity += amount;
	if (InterruptIntensity < 0) InterruptIntensity = 0;
	if (InterruptIntensity > MaxInterruptIntensity) InterruptIntensity = MaxInterruptIntensity;

	float HighestMatch = -1;
	TObjectPtr<UAnimMontage> Montage = nullptr;
	for (TPair Reaction : HitReactionAnimations)
	{
		if (Reaction.Key <= InterruptIntensity && Reaction.Key > HighestMatch)
		{
			HighestMatch = Reaction.Key;
			Montage = Reaction.Value;
		}
	}

	if (ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner()))
	{
		bool CanInterrupt = Owner->AbilityManagerComponent->TryInterrput(InterruptIntensity);
		if (CanInterrupt)
		{
			if (ACharacter* character = Cast<ACharacter>(GetOwner()))
			{
				UAnimInstance* animInstance = character->GetMesh()->GetAnimInstance();
				animInstance->Montage_Play(Montage,1.0f);
			}
		}
	}
}
