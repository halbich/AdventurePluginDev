// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginStoryEngineEditorModule.h"
#include "AdventurePluginStoryEngineEditorStyle.h"
#include "AdventurePluginStoryEngineEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ContentBrowserModule.h"
#include "ContentBrowserDelegates.h"
#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "PropertyEditorDelegates.h"
#include "AdventurePluginEditor.h"
#include "AssetTypeActions_QuestGraph.h"
#include "StoryEngine/Structs/QuestGraphFlag.h"
#include "StoryEngine/Structs/QuestGraphBool.h"
#include "StoryEngine/Structs/QuestGraphString.h"
#include "StoryEngine/Structs/QuestGraphInteger.h"
#include "StoryEngine/Structs/QuestGraphEvent.h"
#include "StoryEngine/Graph/QuestGraphNode_Inventory.h"
#include "Customizations/QuestGraphFlagCustomization.h"
#include "Customizations/QuestGraphBoolCustomization.h"
#include "Customizations/QuestGraphStringCustomization.h"
#include "Customizations/QuestGraphIntegerCustomization.h"
#include "Customizations/QuestGraphEventCustomization.h"
#include "Customizations/QuestInventoryItemCustomization.h"
#include "SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"

const FName AdventurePluginStoryEngineEditorAppIdentifier = FName(TEXT("AdventurePluginStoryEngineEditorApp"));

#define LOCTEXT_NAMESPACE "FAdventurePluginStoryEngineEditorModule"

void FAdventurePluginStoryEngineEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FAdventurePluginStoryEngineEditorStyle::Initialize();
	FAdventurePluginStoryEngineEditorStyle::ReloadTextures();
	FAdventurePluginStoryEngineEditorCommands::Register();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	FAdventurePluginEditor& AdventurePluginEditor = FAdventurePluginEditor::Get();
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_QuestGraph(AdventurePluginEditor.DefaultAssetCategory())));

	/* Adding custom asset icon */
	StyleSet = MakeShareable(new FSlateStyleSet("StoryEngineStyle"));
	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	StyleSet->Set("ClassIcon.QuestGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_16x.png")), FVector2D(16.0f, 16.0f)));
	StyleSet->Set("ClassThumbnail.QuestGraph", new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Icons/AssetIcons/BehaviorTree_64x.png")), FVector2D(64.0f, 64.0f)));
	//StyleSet->Set("ClassIcon.MyComponent", new FSlateImageBrush("path/to/MyComponent16.png", FVector2D(16.0f, 16.0f)));
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	//FClassIconFinder::RegisterIconSource(&StyleSet.Get());
	/**/

	/* Registering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UQuestGraphNode_Inventory::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FQuestInventoryItemCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphFlag::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphFlagCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphBool::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphBoolCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphInteger::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphIntegerCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphString::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphStringCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(FQuestGraphEvent::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FQuestGraphEventCustomization::MakeInstance));
	/**/
}

void FAdventurePluginStoryEngineEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAdventurePluginStoryEngineEditorStyle::Shutdown();
	FAdventurePluginStoryEngineEditorCommands::Unregister();

	/* Unregistering custom property layouts */
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(UQuestGraphNode_Inventory::StaticClass()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphFlag::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphBool::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphInteger::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphString::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FQuestGraphEvent::StaticStruct()->GetFName());
	/**/

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
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	ensure(StyleSet.IsUnique());
	StyleSet.Reset();
	/**/
}

void FAdventurePluginStoryEngineEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdventurePluginStoryEngineEditorModule, AdventurePluginStoryEngineEditor)