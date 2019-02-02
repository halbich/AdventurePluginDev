// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginDialogEditorModule.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "SlateOptMacros.h"
#include "GraphEditor.h"
#include "Framework/Commands/GenericCommands.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Materials/Material.h"
#include "EdGraph/EdGraphSchema.h"
#include "AssetToolsModule.h"
#include "IAssetTypeActions.h"
#include "AssetTypeActions_DialogGraph.h"
#include "ClassIconFinder.h"
#include "SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "PropertyEditorModule.h"
#include "PropertyEditorDelegates.h"
#include "Dialog/Graph/DialogGraph.h"
#include "Dialog/Graph/DialogGraphNode_Goto.h"
#include "Dialog/Graph/DialogGraphNode_IfInInventory.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_PlayAnimationBase.h"
#include "Dialog/Graph/BaseClasses/DialogGraphNode_DialogLineBase.h"
#include "Dialog/Structs/DialogGraphEntryPoint.h"
#include "Customizations/GotoCustomization.h"
#include "Customizations/DialogGraphCustomization.h"
#include "Customizations/DialogInventoryItemCustomization.h"
#include "Customizations/DialogGraphEntryPointCustomization.h"
#include "Customizations/AnimationCustomization.h"
#include "Customizations/DialogLineCustomization.h"

static const FName AdventurePluginDialogEditorTabName("AdventurePluginDialogEditor");
//const FName DialogEditorAppIdentifier = FName(TEXT("DialogEditorApp"));

#define LOCTEXT_NAMESPACE "FAdventurePluginDialogEditorModule"

void FAdventurePluginDialogEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module


	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	FAdventurePluginEditor& AdventurePluginEditor = FAdventurePluginEditor::Get();
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_DialogGraph(AdventurePluginEditor.DefaultAssetCategory())));

	/* Adding custom asset icon */
	StyleSet = MakeShareable(new FSlateStyleSet("DialogStyle"));
	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	StyleSet->Set("ClassIcon.DialogGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_16x.png")), FVector2D(16.0f, 16.0f)));
	StyleSet->Set("ClassThumbnail.DialogGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_64x.png")), FVector2D(64.0f, 64.0f)));
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());

	/* Registering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UDialogGraph::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FDialogGraphCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(UDialogGraphNode_Goto::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FGotoCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(UDialogGraphNode_PlayAnimationBase::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FAnimationCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(UDialogGraphNode_DialogLineBase::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FDialogLineCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(UDialogGraphNode_IfInInventory::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FDialogInventoryItemCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FDialogGraphEntryPoint::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FDialogGraphEntryPointCustomization::MakeInstance));
	/**/
}

void FAdventurePluginDialogEditorModule::ShutdownModule()
{

	/* Unregistering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(UDialogGraph::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomClassLayout(UDialogGraphNode_Goto::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomClassLayout(UDialogGraphNode_PlayAnimationBase::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomClassLayout(UDialogGraphNode_IfInInventory::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FDialogGraphEntryPoint::StaticStruct()->GetFName());

	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}
	/* Removing custom asset icon */
	//FClassIconFinder::UnregisterIconSource(&StyleSet.Get());
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	ensure(StyleSet.IsUnique());
	StyleSet.Reset();
	/**/
}

void FAdventurePluginDialogEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdventurePluginDialogEditorModule, AdventurePluginDialogEditor)
