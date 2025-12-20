// Fill out your copyright notice in the Description page of Project Settings.


#include "MVVM_Ability.h"

void UMVVM_Ability::SetCooldown(float newCooldown)
{
	if (Cooldown != newCooldown)
	{
		Cooldown = newCooldown;
		CooldownPercent = MaxCooldown == 0 ? 0 : Cooldown / MaxCooldown;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Cooldown);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CooldownPercent);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCooldown);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCooldownPercent);
	}
}
void UMVVM_Ability::SetMaxCooldown(float newMaxCooldown)
{
	if (MaxCooldown != newMaxCooldown)
	{
		MaxCooldown = newMaxCooldown;
		CooldownPercent = MaxCooldown == 0 ? 0 : Cooldown / MaxCooldown;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MaxCooldown);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CooldownPercent);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxCooldown);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCooldownPercent);
	}
}
void UMVVM_Ability::SetKeyHint(FString newKeyHint)
{
	if (KeyHint != newKeyHint)
	{
		KeyHint = newKeyHint;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(KeyHint);
	}
}