#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"
#include "IAssetTools.h"
#include "AdventurePluginEditor.h"

/**
 * The module takes care of registering asset type actions and property editor customizations
 * for Adventure Plugin classes related to the quest system, and also registers editor nodes
 * for corresponding quest runtime nodes.
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