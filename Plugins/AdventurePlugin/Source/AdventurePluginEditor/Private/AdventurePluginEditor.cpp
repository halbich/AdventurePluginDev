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

#undef LOCTEXT_NAMESPACE