#include "Common/AdventurePluginGameContext.h"
#include "Inventory/Controller/InventoryController.h"
#include "Inventory/Presenter/InventoryPresenterInterface.h"
#include "Dialog/Controller/DialogController.h"
#include "Dialog/Presenter/DialogPresenterInterface.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "Inventory/ItemManager.h"
#include "AdventurePluginRuntime.h"
#include "Common/AdventurePluginGameInstanceInterface.h"
#include "AdventureCharacterManager.h"

bool UAdventurePluginGameContext::IsGameContextValid(const UAdventurePluginGameContext* GameContext, const FString& Caller)
{
	if (!IsValid(GameContext) ||
		!IsValid(GameContext->InventoryController) ||
		!IsValid(GameContext->InventoryPresenter.GetObject()) ||
		!IsValid(GameContext->DialogController) ||
		!IsValid(GameContext->DialogPresenter.GetObject()) ||
		!IsValid(GameContext->SaveGame) ||
		!IsValid(GameContext->ItemManager) ||
		!IsValid(GameContext->AdventureCharacterManager))
	{
		FText ValidText(NSLOCTEXT("AdventurePlugin", "ValidConstant", "Valid"));
		FText InvalidText(NSLOCTEXT("AdventurePluugin", "InvalidConstant", "Invalid"));

		FFormatOrderedArguments FormatArgs{
			FText::FromString(Caller),
			IsValid(GameContext) ? ValidText : InvalidText,
			IsValid(GameContext) && IsValid(GameContext->InventoryController) ? ValidText : InvalidText,
			IsValid(GameContext) && IsValid(GameContext->InventoryPresenter.GetObject()) ? ValidText : InvalidText,
			IsValid(GameContext) && IsValid(GameContext->DialogController) ? ValidText : InvalidText,
			IsValid(GameContext) && IsValid(GameContext->DialogPresenter.GetObject()) ? ValidText : InvalidText,
			IsValid(GameContext) && IsValid(GameContext->SaveGame) ? ValidText : InvalidText,
			IsValid(GameContext) && IsValid(GameContext->ItemManager) ? ValidText : InvalidText,
			IsValid(GameContext) && IsValid(GameContext->AdventureCharacterManager) ? ValidText : InvalidText
			};

		FText ErrorText =  FText::Format(NSLOCTEXT("AdventurePlugin", "GameContextInvalid", "{0}: Game context or one of its subclasses is null or invalid. GameContext:{1}, InventoryController:{2},InventoryPresent:{3},DialogController:{4},DialogPresenter:{5},SaveGame:{6},ItemManager:{7},AdventureCharacterManager:{8}"),
			FormatArgs
			);
		LOG_Error(ErrorText);
		return false;
	}
	return true;
}
UAdventurePluginGameContext* UAdventurePluginGameContext::ResolveGameContext(UAdventurePluginGameContext* GameContextOverride, UObject* WorldObjectContext) {
	if (IsValid(GameContextOverride)) {
		return GameContextOverride;
	}
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldObjectContext);
	if (IsValid(GameInstance) && GameInstance->GetClass()->ImplementsInterface(UAdventurePluginGameInstanceInterface::StaticClass())) 
	{
		return IAdventurePluginGameInstanceInterface::Execute_GetDefaultGameContext(GameInstance);
	}
	return nullptr;
}