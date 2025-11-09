// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyEnums.h"
#include "AnimNotify_AttackEvent.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UAnimNotify_AttackEvent : public UAnimNotify
{
	GENERATED_BODY()


public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Anim")
	EAttackEventType AttackEventType = EAttackEventType::NONE;
};
