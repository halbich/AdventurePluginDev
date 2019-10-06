#include "InteractableSceneObject.h"
#include "SaveGame/AdventurePluginSaveGame.h"
#include "Common/AdventurePluginGameContext.h"
#include "BlueprintLibrary/AdventurePluginBlueprintLibrary.h"

void UInteractableSceneObject::Examine_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	UAdventurePluginBlueprintLibrary::ShowDialogFromEntryPoint(GameContext, ExamineDialog, this);
	SetWasExamined(GameContext, true);
}

void UInteractableSceneObject::Use_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
}

bool UInteractableSceneObject::IsExaminable_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
	return bDefaultIsExaminable;
}

bool UInteractableSceneObject::IsUsable_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
	return bDefaultIsUsable;
}

bool UInteractableSceneObject::WasExamined_Implementation(UAdventurePluginGameContext* GameContextOverride)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	return GameContext->SaveGame->GetBoolOrDefault(GetWasExaminedPropertyName(), false);
}
void UInteractableSceneObject::SetWasExamined_Implementation(UAdventurePluginGameContext* GameContextOverride, bool bWasExamined)
{
	auto* GameContext = UAdventurePluginGameContext::ResolveGameContext(GameContextOverride, this);
	GameContext->SaveGame->SetBool(GetWasExaminedPropertyName(), bWasExamined);
}

FName UInteractableSceneObject::GetWasExaminedPropertyName_Implementation()
{
	return FName(*("Examined_" + GetFullName()));
}