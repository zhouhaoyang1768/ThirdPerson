// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnProjectile.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UAnimNotify_SpawnProjectile : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = "Anim")
	float Velocity;

	UPROPERTY(EditAnywhere, Category = "Anim")
	FTransform Transform;

	UPROPERTY(EditAnywhere, Category = "Anim")
	TSubclassOf<class AActor> ProjectileClass;
};
