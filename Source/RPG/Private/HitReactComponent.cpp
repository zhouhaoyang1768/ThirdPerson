// Fill out your copyright notice in the Description page of Project Settings.


#include "HitReactComponent.h"
#include "GameplayTagsManager.h"
#include "PlayMontageCallbackProxy.h"
#include "RPGCharacter.h"

// UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_Ability_Supressed, "Character.Ability.Supressed", "The character is being hit and interrupted")


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
	UGameplayTagsManager& gpmanager = UGameplayTagsManager::Get();
	InterruptedTag = gpmanager.RequestGameplayTag(FName("Character.Ability.Supressed"));
	Super::BeginPlay();

	if(ACharacterBase* const Character = Cast<ACharacterBase>(GetOwner()))
	{
		// Character->OnCharacterTageDamage.AddDynamic(this, &ThisClass::OnCharacterTakeDamage);
	}

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

	if (ACharacterBase* Owner = Cast<ACharacterBase>(GetOwner()))
	{
		bool CanInterrupt = Owner->AbilityManagerComponent->TryInterrput(InterruptIntensity);
		if (CanInterrupt)
		{
			Owner->AddGameplayTagToCharacter(InterruptedTag);
			
			UAnimInstance* animInstance = Owner->GetMesh()->GetAnimInstance();
			/*UPlayMontageCallbackProxy* PlayMontageCallbackProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(
				Owner->GetMesh(), Montage
			);*/
			GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, IsValid(Montage) ? "valid" : "not valid");
			//PlayMontageCallbackProxy->OnCompleted.AddDynamic(this, &ThisClass::OnInterruptEnd);
			//PlayMontageCallbackProxy->OnInterrupted.AddDynamic(this, &ThisClass::OnInterruptEnd);


			FOnMontageEnded OnMontageEnded;
			OnMontageEnded.BindUFunction(this, FName("OnInterruptEnd"));

			animInstance->StopAllMontages(0);
			animInstance->Montage_SetEndDelegate(OnMontageEnded, Montage);
			animInstance->Montage_Play(Montage,1.0f);
		}
	}
}


void UHitReactComponent::OnInterruptEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "interrupt end");
	if (ACharacterBase* const Character = Cast<ACharacterBase>(GetOwner()))
	{
		Character->RemoveGameplayTagFromCharacter(InterruptedTag);
	}
}


void UHitReactComponent::OnCharacterTakeDamage(float Damage)
{
	IncreaseIntensity(Damage);
}