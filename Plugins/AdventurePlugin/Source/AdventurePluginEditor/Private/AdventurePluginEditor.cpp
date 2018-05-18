// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "MessageLogModule.h"
#include "MessageLogInitializationOptions.h"
#include "IAdventurePluginEditor.h"


#define LOCTEXT_NAMESPACE "AdventurePluginEditor"

class FAdventurePluginEditor : public IAdventurePluginEditor
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void Log(EMessageSeverity::Type EngineMessageSeverity, const FText& Message) const;

	virtual void Log(const TSharedRef< class FTokenizedMessage >& Message) const;
};

IMPLEMENT_MODULE( FAdventurePluginEditor, AdventurePluginEditor )



void FAdventurePluginEditor::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)

	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	{
		FMessageLogInitializationOptions InitOptions;
		InitOptions.bShowFilters = true;
		MessageLogModule.RegisterLogListing("AdventurePluginLog", LOCTEXT("AdventurePluginLog", "Adventure Plugin Log"), InitOptions);
	}

}


void FAdventurePluginEditor::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
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