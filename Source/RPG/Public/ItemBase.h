// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.generated.h"

/**
 * 
 */
class ACharacterBase;

UCLASS(Blueprintable, BlueprintType)
class RPG_API UItemBase : public UObject
{
	GENERATED_BODY()
public:
	UItemBase();
	~UItemBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACharacterBase* Owner;

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* Mesh;



public:
	UFUNCTION(BlueprintPure)
	FString GetName() const { return Name; }
	UStaticMesh* GetMesh() { return Mesh; }
	virtual void OnPickup(ACharacterBase* NewOwner) {}
	virtual void OnDrop() {}
	virtual bool Use(AActor* target) { return false; }
};
