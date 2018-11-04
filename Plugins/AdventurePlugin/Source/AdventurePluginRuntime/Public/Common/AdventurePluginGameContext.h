// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory/Controller/InventoryController.h"
#include "Inventory/Presenter/InventoryPresenterInterface.h"
//#include "Dialogue/Controller/DialogueController.h"
//#include "Dialogue/Presenter/DialoguePresenterInterface.h"
#include "AdventurePluginConfig.h"
#include "AdventurePluginGameContext.generated.h"

class UDialogueController;
class IDialoguePresenterInterface;

/**
 * 
 */
UCLASS()
class ADVENTUREPLUGINRUNTIME_API UAdventurePluginGameContext : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Transient)
	UInventoryController* InventoryController;
	

	UPROPERTY(Transient)
	TScriptInterface< IInventoryPresenterInterface> InventoryPresenter;

	
	UPROPERTY(Transient)
		UDialogueController* DialogueController;

	UPROPERTY(Transient)
		TScriptInterface< IDialoguePresenterInterface> DialoguePresenter;
	
};
