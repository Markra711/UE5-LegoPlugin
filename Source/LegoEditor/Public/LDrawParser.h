// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LegoModel.h"

class LEGOEDITOR_API LDrawParser
{

public:
	/**
	 * Parses an LDraw file.
	 *
	 * @param FilePath   Absolute path to .ldr file
	 * @param RootModelName Name of the model containing all submodels
	 * @param OutModels  Parsed models
	 * @param OutError   Error message if parsing fails
	 * @return true if successful
	 */
	bool ParseFile(const FString& FilePath, FString& RootModelName, TMap<FString, FLegoModel>& OutModels, FString& OutError);
};
