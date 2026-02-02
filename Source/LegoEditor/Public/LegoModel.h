// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LegoPart.h"

struct LEGOEDITOR_API FLegoModel
{
	FString Name;

	TArray<FLegoPart> Parts;
};

