// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "DroppedItem.h"
#include "CharacterBase.h"
#include "MVVM_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UMVVM_Pickup : public UMVVMViewModelBase
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, FieldNotify)
	TArray<ADroppedItem*> DroppedItems;

	const static int MaxItemsCount = 3;

	UPROPERTY(EditAnywhere, FieldNotify)
	int Cursor = 0;

	bool ItemsUpdated = false;

	void AdjustCursor();

public:
	UFUNCTION(BlueprintCallable) 
	void Reset() { DroppedItems.Reset(); }

	UFUNCTION(BlueprintCallable)
	bool IsItemsUpdated() const { return ItemsUpdated; }

	UFUNCTION(BlueprintCallable)
	void AcknowledgeUpdate() { ItemsUpdated = false; }

	UFUNCTION(BlueprintPure, FieldNotify)
	int GetCursor() const { return Cursor; }

	UFUNCTION(BlueprintPure, FieldNotify)
	TArray<ADroppedItem*> GetDroppedItems() const { return DroppedItems; }

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ACharacterBase> Host;

	UFUNCTION(BlueprintCallable)
	void Add(ADroppedItem* Item);

	UFUNCTION(BlueprintCallable)
	void Remove(ADroppedItem* Item);


	UFUNCTION(BlueprintCallable)
	void CursorUp();

	UFUNCTION(BlueprintCallable)
	void CursorDown();
};
