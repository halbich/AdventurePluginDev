// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAdventurePluginRuntime.h"

#define LOCTEXT_NAMESPACE "CustomSettings"

#pragma optimize("",off)

class FAdventurePluginRuntime : public IAdventurePluginRuntime
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Callback for when the settings were saved.
	bool HandleSettingsSaved() {
		UAdventurePluginConfig* Settings = GetMutableDefault<UAdventurePluginConfig>();
		bool ResaveSettings = false;

		// You can put any validation code in here and resave the settings in case an invalid // value has been entered

		if (ResaveSettings) {
			Settings->SaveConfig();
		}

		return true;
	}

	void RegisterSettings() {
		// Registering some settings is just a matter of exposing the default UObject of
		// your desired class, feel free to add here all those settings you want to expose
		// to your LDs or artists.

		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
			// Create the new category
			ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

			SettingsContainer->DescribeCategory("CustomSettings",
				LOCTEXT("RuntimeWDCategoryName", "CustomSettings"),
				LOCTEXT("RuntimeWDCategoryDescription", "Game configuration for the CustomSettings game module"));

			// Register the settings
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "CustomSettings", "General",
				LOCTEXT("RuntimeGeneralSettingsName", "General"),
				LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for our game module"), GetMutableDefault<UAdventurePluginConfig>());

			// Register the save handler to your settings, you might want to use it to
			// validate those or just act to settings changes.
			if (SettingsSection.IsValid()) {
				SettingsSection->OnModified().BindRaw(this, &FAdventurePluginRuntime::HandleSettingsSaved);
			}
		}
	}

	void UnregisterSettings() {
		// Ensure to unregister all of your registered settings here, hot-reload would
		// otherwise yield unexpected results.

		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
			SettingsModule->UnregisterSettings("Project", "CustomSettings", "General");
		}
	}
};


#pragma optimize("",on)

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdventurePluginRuntime, AdventurePluginRuntime)

void FAdventurePluginRuntime::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	RegisterSettings();
}

void FAdventurePluginRuntime::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (UObjectInitialized()) {
		UnregisterSettings();
	}
}