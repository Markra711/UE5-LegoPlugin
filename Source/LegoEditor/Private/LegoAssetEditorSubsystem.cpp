// Fill out your copyright notice in the Description page of Project Settings.


#include "LegoAssetEditorSubsystem.h"

#include "AssetRegistry/AssetRegistryModule.h"

void ULegoAssetEditorSubsystem::Initialize(
	FSubsystemCollectionBase& Collection
)
{
	Super::Initialize(Collection);

	// Set path to ColorMap asset
	MaterialLibraryAsset = TSoftObjectPtr<ULegoMaterialLibrary>(
		FSoftObjectPath(
			TEXT("/Lego/LegoMaterials/LegoMaterialLibrary.LegoMaterialLibrary")
		)
	);

	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	AssetRegistryModule.Get().OnFilesLoaded().AddUObject(
		this,
		&ULegoAssetEditorSubsystem::OnAssetRegistryReady
	);
}

void ULegoAssetEditorSubsystem::OnAssetRegistryReady()
{
	BuildMeshCache();
	BuildMaterialCache();

	UE_LOG(LogTemp, Log,
		TEXT("LegoAssetSubsystem initialized: %d meshes, %d materials"),
		MeshCache.Num(),
		MaterialCache.Num()
	);
}

void ULegoAssetEditorSubsystem::Deinitialize()
{
	MeshCache.Empty();
	MaterialCache.Empty();

	Super::Deinitialize();
}

void ULegoAssetEditorSubsystem::BuildMeshCache()
{
	MeshCache.Empty();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.PackagePaths.Add(*LegoPartsPath);
	Filter.bRecursivePaths = true;

	TArray<FAssetData> AssetData;
	AssetRegistry.GetAssets(Filter, AssetData);

	for (const FAssetData& Asset : AssetData)
	{
		MeshCache.Add(
			Asset.AssetName,
			TSoftObjectPtr<UStaticMesh>(Asset.GetSoftObjectPath())
		);
	}

	UE_LOG(LogTemp, Log,
		TEXT("Lego mesh cache built: %d meshes"),
		MeshCache.Num()
	);
}

void ULegoAssetEditorSubsystem::BuildMaterialCache()
{
	MaterialCache.Empty();

	ULegoMaterialLibrary* MaterialLibrary = MaterialLibraryAsset.LoadSynchronous();
	if (!MaterialLibrary)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Failed to load LDrawColorMap asset")
		);
		return;
	}

	for (const FLegoMaterialEntry& Entry : MaterialLibrary->Entries)
	{
		if (Entry.Material)
		{
			MaterialCache.Add(
				Entry.ColorID,
				Entry.Material
			);
		}
	}
}

UStaticMesh* ULegoAssetEditorSubsystem::GetMesh(
	const FString& PartName
)
{
	const TSoftObjectPtr<UStaticMesh>* Entry =
		MeshCache.Find(FName(*PartName));

	if (!Entry)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("LegoAssetEditorRegistry: Missing mesh for part %s"),
			*PartName
		);
		return nullptr;
	}

	return Entry->LoadSynchronous();
}

UMaterialInterface* ULegoAssetEditorSubsystem::GetMaterial(
	int32 ColorCode
)
{
	if (UMaterialInterface** Mat =
		MaterialCache.Find(ColorCode))
	{
		return *Mat;
	}

	UE_LOG(LogTemp, Warning,
		TEXT("Missing material for color %d"),
		ColorCode
	);

	return nullptr;
}