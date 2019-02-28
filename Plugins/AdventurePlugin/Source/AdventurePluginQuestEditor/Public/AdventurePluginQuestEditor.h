
#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Styling/SlateStyle.h"
#include "IAssetTools.h"
#include "AdventurePluginEditor.h"

extern const FName AdventurePluginQuestEditorAppIdentifier;
/**
* This module registers the asset editor for QuestGraph asset. It also registers some customizations relevant to quests.
*/
class FAdventurePluginQuestEditor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	TSharedPtr<FSlateStyleSet> StyleSet;
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};