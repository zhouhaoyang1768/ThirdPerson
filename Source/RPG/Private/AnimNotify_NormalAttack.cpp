// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_NormalAttack.h"
#include "CombatAttacker.h"


void UAnimNotify_NormalAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if (ICombatAttacker* AttackerInterface = Cast<ICombatAttacker>(MeshComp->GetOwner()))
	{
		// tell the actor to check for combo string
		AttackerInterface->DoNormalAttack();
	}
}