// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Components/ActorComponent.h"
#include "Animation/AnimMontage.h"
#include "Containers/Map.h"
#include "HitReactComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UHitReactComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitReactComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TMap<float, TObjectPtr<UAnimMontage>> HitReactionAnimations;

	UPROPERTY(BlueprintReadOnly)
	float InterruptIntensity;

	UPROPERTY(EditDefaultsOnly)
	float MaxInterruptIntensity;

	UPROPERTY(EditDefaultsOnly)
	float InterruptIntensityRecoveryRate;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void IncreaseIntensity(float amount);
};
