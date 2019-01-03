// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginEditor.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "SlateApplication.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/SlateDelegates.h"
#include "MessageLogModule.h"
#include "MessageLogInitializationOptions.h"
#include "LevelEditor.h"
#include "AssetToolsModule.h"
#include "AdventurePluginEditorToolBar.h"
#include "AdventurePluginEditorStyle.h"
#include "AdventurePluginEditorCommands.h"
#include "AssetTypeActions_AdventureCharacter.h"
#include "AssetTypeActions_InventoryItem.h"
#include "IconThumbnailRenderer.h"
#include "GenericGraph/GenericGraphEditorStyle.h"

#define LOCTEXT_NAMESPACE "AdventurePluginEditor"

IMPLEMENT_MODULE(FAdventurePluginEditor, AdventurePluginEditor)


const FName APLogName("AdventurePluginLog");


void FAdventurePluginEditor::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)

	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	{
		FMessageLogInitializationOptions InitOptions;
		InitOptions.bShowFilters = true;
		MessageLogModule.RegisterLogListing(APLogName, LOCTEXT("AdventurePluginLog", "Adventure Plugin Log"), InitOptions);
	}

	// Note this must come before any tab spawning because that can create the SLevelEditor and attempt to map commands
	FAdventurePluginEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FAdventurePluginEditor::AddToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AdventurePluginAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("AdventurePlugin")), LOCTEXT("AdventurePluginAssetCategory", "Adventure Plugin"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_AdventureCharacter(AdventurePluginAssetCategory)));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_InventoryItem(AdventurePluginAssetCategory)));

	UThumbnailManager::Get().RegisterCustomRenderer(UAdventureCharacter::StaticClass(), UIconThumbnailRenderer::StaticClass());
	UThumbnailManager::Get().RegisterCustomRenderer(UInventoryItem::StaticClass(), UIconThumbnailRenderer::StaticClass());

	FGenericGraphEditorStyle::Initialize();

	RegisterSettings();
}

void FAdventurePluginEditor::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateStatic(&FAdventurePluginEditorToolBar::GeneratePluginMenu, PluginCommands.ToSharedRef()),
		LOCTEXT("AdventurePluginEditorMenuCombo", "Adventure Editor"),
		LOCTEXT("AdventurePluginEditorMenuCombo_ToolTip", "Adventure Editor menu combo button"),
		FSlateIcon(FAdventurePluginEditorStyle::GetStyleSetName(), "AdventurePlugin.MenuButton"),
		false,
		"LevelToolbarAdventurePluginEditorMenuCombo"
	);
}

void FAdventurePluginEditor::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.


	if (UObjectInitialized())
	{
		UnregisterSettings();

		UThumbnailManager::Get().UnregisterCustomRenderer(UAdventureCharacter::StaticClass());
		UThumbnailManager::Get().UnregisterCustomRenderer(UInventoryItem::StaticClass());
	}

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	FGenericGraphEditorStyle::Shutdown();

	if (FModuleManager::Get().IsModuleLoaded("MessageLog"))
	{
		FMessageLogModule& MessageLogModule = FModuleManager::GetModuleChecked<FMessageLogModule>("MessageLog");
		MessageLogModule.UnregisterLogListing(APLogName);
	}

	ToolBarExtensibilityManager.Reset();

	FAdventurePluginEditorCommands::Unregister();
}

void FAdventurePluginEditor::Log(const TSharedRef< class FTokenizedMessage >& Message) const
{
	if (GIsEditor)
	{
		FMessageLog SlateStyleLog("AdventurePluginLog");
		SlateStyleLog.AddMessage(Message);

		if (Message->GetSeverity() <= EMessageSeverity::Warning)
		{
			SlateStyleLog.Open();
		}
	}
}

void FAdventurePluginEditor::Log(EMessageSeverity::Type EngineMessageSeverity, const FText& Message) const
{
	/*EMessageSeverity::Type EngineMessageSeverity = EMessageSeverity::CriticalError;
	switch (Severity)
	{
	case EAPMessageSeverity::CriticalError: EngineMessageSeverity = EMessageSeverity::CriticalError; break;
	case EAPMessageSeverity::Error: EngineMessageSeverity = EMessageSeverity::Error; break;
	case EAPMessageSeverity::PerformanceWarning: EngineMessageSeverity = EMessageSeverity::PerformanceWarning; break;
	case EAPMessageSeverity::Warning: EngineMessageSeverity = EMessageSeverity::Warning; break;
	case EAPMessageSeverity::Info: EngineMessageSeverity = EMessageSeverity::Info; break;
	}
*/
	if (GIsEditor)
	{
		FMessageLog SlateStyleLog("AdventurePluginLog");
		SlateStyleLog.AddMessage(FTokenizedMessage::Create(EngineMessageSeverity, Message));

		if (EngineMessageSeverity <= EMessageSeverity::Warning)
		{
			SlateStyleLog.Open();
		}
	}
}


// Callback for when the settings were saved.
bool FAdventurePluginEditor::HandleSettingsSaved() {
	UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid // value has been entered

	if (ResaveSettings) {
		Settings->SaveConfig();
	}

	return true;
}

void FAdventurePluginEditor::RegisterSettings()
{
	// Registering some settings is just a matter of exposing the default UObject of
	// your desired class, feel free to add here all those settings you want to expose
	// to your LDs or artists.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "AdventurePlugin",
			LOCTEXT("SettingsGeneralSectionName", "Adventure Plugin"),
			LOCTEXT("SettingsGeneralSectionDescription", "Base configuration for the Adventure Plugin"), GetMutableDefault<UAdventurePluginConfig>());

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid()) {
			SettingsSection->OnModified().BindRaw(this, &FAdventurePluginEditor::HandleSettingsSaved);
		}
	}
}

void FAdventurePluginEditor::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
		SettingsModule->UnregisterSettings("Project", "APSettings", "AdventurePlugin");
	}
}

void FAdventurePluginEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}


#undef LOCTEXT_NAMESPACE