// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_Ability.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UMVVM_Ability : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Getter, Setter, FieldNotify, meta = (AllowPrivateAccess))
	float Cooldown;

	UPROPERTY(EditAnywhere, Getter, Setter, FieldNotify, meta = (AllowPrivateAccess))
	float MaxCooldown;

	UPROPERTY(EditAnywhere, Getter, FieldNotify, meta = (AllowPrivateAccess))
	float CooldownPercent;

	UPROPERTY(EditAnywhere, Getter, Setter, FieldNotify, meta = (AllowPrivateAccess))
	FString KeyHint;
public:
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetCooldown() const { return Cooldown; }
	UFUNCTION(BlueprintCallable)
	void SetCooldown(float newCooldown);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetMaxCooldown() const { return MaxCooldown; }
	UFUNCTION(BlueprintCallable)
	void SetMaxCooldown(float newMaxCooldown);

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetKeyHint() const { return KeyHint; }
	UFUNCTION(BlueprintCallable)
	void SetKeyHint(FString newKeyHint);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetCooldownPercent() const { return Cooldown / MaxCooldown; }
};
