// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAttackEventType : uint8
{
	NONE						UMETA(DisplayName = "None"),
	ATTACH_LEFT_HAND			UMETA(DisplayName = "Attach To Left Hand"),
	ATTACH_RIGHT_HAND			UMETA(DisplayName = "Attach To Right Hand"),
	ATTACH_RIGHT_FOOT			UMETA(DisplayName = "Attach To Right Foot"),
	DETACH						UMETA(DisplayName = "Detach"),
};
