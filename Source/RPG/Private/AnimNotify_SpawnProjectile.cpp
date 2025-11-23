// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SpawnProjectile.h"
#include "CharacterBase.h"

void UAnimNotify_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ACharacterBase* const Character = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		FTransform CharacterTransform = Character->GetTransform();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;
		SpawnParams.Instigator = Character;
		SpawnParams.bNoFail = true;
		Character->GetWorld()->SpawnActor(ProjectileClass, &CharacterTransform, SpawnParams);
		
		
	}
}