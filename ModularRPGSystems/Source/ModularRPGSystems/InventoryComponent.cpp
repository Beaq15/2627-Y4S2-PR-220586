// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemDefinition.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UInventoryComponent::AddItem(UItemDefinition* Definition, int32 Count)
{
	if (!Definition || Count <= 0) return 0;

	int32 Remaining = Count;

	// Fill existing stacks of the same item first
	for (FInventoryEntry& Entry : Entries)
	{
		if (Remaining <= 0) break;

		if (Entry.Definition && Entry.Definition->ItemTag == Definition->ItemTag)
		{
			const int32 ToAdd = FMath::Min(Definition->MaxStackSize - Entry.Count, Remaining);
			if (ToAdd > 0)
			{
				Entry.Count += ToAdd;
				Remaining -= ToAdd;
			}
		}
	}

	// Move to the next available slot
	while (Remaining > 0 && Entries.Num() < MaxSlots)
	{
		FInventoryEntry NewEntry;
		NewEntry.Definition = Definition;
		NewEntry.Count = FMath::Min(Definition->MaxStackSize, Remaining);
		Remaining -= NewEntry.Count;
		Entries.Add(NewEntry);
	}

	const int32 Added = Count - Remaining;

	if (Added > 0)
		OnItemAdded.Broadcast(Definition->ItemTag, Added);

	return Added;
}

int32 UInventoryComponent::RemoveItem(FGameplayTag ItemTag, int32 Count)
{
	if (!ItemTag.IsValid() || Count <= 0) return 0;

	int32 Remaining = Count;

	//Remove from the last stack first
	for (int32 i = Entries.Num() - 1; i >= 0 && Remaining > 0; i--)
	{
		FInventoryEntry& Entry = Entries[i];
		if (Entry.Definition && Entry.Definition->ItemTag == ItemTag)
		{
			const int32 ToRemove = FMath::Min(Entry.Count, Remaining);
			Entry.Count -= ToRemove;
			Remaining -= ToRemove;

			if (Entry.Count <= 0)
				Entries.RemoveAt(i);
		}
	}

	const int32 Removed = Count - Remaining;

	if (Removed > 0)
		OnItemRemoved.Broadcast(ItemTag, Removed);

	return Removed;
}

int32 UInventoryComponent::GetItemCount(FGameplayTag ItemTag) const
{
	int32 Total = 0;
	
	for (const FInventoryEntry& Entry : Entries)
	{
		if (Entry.Definition && Entry.Definition->ItemTag == ItemTag)
			Total += Entry.Count;
	}

	return Total;
}


