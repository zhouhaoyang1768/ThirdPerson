// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackEvent.h"
#include "CharacterBase.h"

void UAnimNotify_AttackEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ACharacterBase* const Character = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		Character->HandleAnimNotify(AttackEventType);
	}
}