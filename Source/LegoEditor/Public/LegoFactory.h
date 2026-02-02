// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "LegoFactory.generated.h"

UCLASS()
class LEGOEDITOR_API ULegoFactory : public UFactory
{
	GENERATED_BODY()
	
private:
	ULegoFactory();

	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};
