// Fill out your copyright notice in the Description page of Project Settings.


#include "MVVM_Pickup.h"

void UMVVM_Pickup::AdjustCursor()
{
	if (Cursor >= DroppedItems.Num())
	{
		Cursor = DroppedItems.Num() - 1;
	}
	if (Cursor < 0)
	{
		Cursor = 0;
	}
}
void UMVVM_Pickup::Add(ADroppedItem* Item)
{
	if (DroppedItems.Num() >= MaxItemsCount) return;
	DroppedItems.AddUnique(Item);
	ItemsUpdated = true;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(DroppedItems);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetDroppedItems);
}

void UMVVM_Pickup::Remove(ADroppedItem* Item)
{
	DroppedItems.Remove(Item);
	AdjustCursor();
	ItemsUpdated = true;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(DroppedItems);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetDroppedItems);
}


void UMVVM_Pickup::CursorUp()
{
	--Cursor;
	AdjustCursor();
	ItemsUpdated = true;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Cursor);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCursor);
}


void UMVVM_Pickup::CursorDown()
{
	++Cursor;
	AdjustCursor();
	ItemsUpdated = true;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Cursor);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCursor);
}