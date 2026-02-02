// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LegoMaterialLibrary.generated.h"

USTRUCT()
struct FLegoMaterialEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=LegoMaterialLibrary)
	int32 ColorID = 0;

	UPROPERTY(EditAnywhere, Category = LegoMaterialLibrary)
	UMaterialInterface* Material = nullptr;
};

UCLASS()
class LEGOEDITOR_API ULegoMaterialLibrary : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = LegoMaterialLibrary)
	TArray<FLegoMaterialEntry> Entries;
};
