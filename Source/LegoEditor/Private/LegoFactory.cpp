// Fill out your copyright notice in the Description page of Project Settings.


#include "LegoFactory.h"
#include "LegoModelBuilder.h"

ULegoFactory::ULegoFactory()
{
	SupportedClass = UStaticMesh::StaticClass();
	Formats.Add(TEXT("ldr;"));
	bCreateNew = false;
	bEditorImport = true;
}

UObject* ULegoFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	LegoModelBuilder ModelBuilder;
	UStaticMesh* Mesh = ModelBuilder.BuildActor(Filename, InParent->GetName());

	return Mesh;
}




