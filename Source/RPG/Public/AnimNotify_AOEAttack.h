// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AOEAttack.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UAnimNotify_AOEAttack : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

protected:
	UPROPERTY(EditAnywhere, Category="Anim")
	float AttackRange = 300.0f;
	
};
