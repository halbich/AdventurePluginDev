// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventurePluginGameContext.h"
#include "InventoryController.h"
#include "InventoryPresenterInterface.h"
#include "DialogController.h"
#include "DialogPresenterInterface.h"
#include "AdventurePluginSaveGame.h"
#include "ItemManager.h"
#include "AdventurePluginRuntime.h"
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

		FText ErrorText =  FText::Format(NSLOCTEXT("AP", "GameContextInvalid", "{0}: Game context or one of its subclasses is null or invalid"),
			FText::FromString(Caller));
		LOG_Error(ErrorText);
		return false;
	}
	return true;
}