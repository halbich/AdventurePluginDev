// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginDialogDebugger.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginDialogDebugger"

FAdventurePluginDialogDebugger::FAdventurePluginDialogDebugger()
{
	DialogAsset = NULL;
	bIsPIEActive = false;

	FEditorDelegates::BeginPIE.AddRaw(this, &FAdventurePluginDialogDebugger::OnBeginPIE);
	FEditorDelegates::EndPIE.AddRaw(this, &FAdventurePluginDialogDebugger::OnEndPIE);
	FEditorDelegates::PausePIE.AddRaw(this, &FAdventurePluginDialogDebugger::OnPausePIE);
}

FAdventurePluginDialogDebugger::~FAdventurePluginDialogDebugger()
{
	FEditorDelegates::BeginPIE.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);
	FEditorDelegates::PausePIE.RemoveAll(this);
}

void FAdventurePluginDialogDebugger::Refresh()
{
	//CacheRootNode();

	if (IsPIESimulating() && IsDebuggerReady())
	{
		// make sure is grabs data if currently paused
		/*if (IsPlaySessionPaused() && TreeInstance.IsValid())
		{
			FindLockedDebugActor(GEditor->PlayWorld);

			UpdateDebuggerInstance();
			UpdateAvailableActions();

			if (DebuggerInstanceIndex != INDEX_NONE)
			{
				UpdateDebuggerViewOnStepChange();
				UpdateDebuggerViewOnTick();

				const FBehaviorTreeDebuggerInstance& ShowInstance = TreeInstance->DebuggerSteps[ActiveStepIndex].InstanceStack[DebuggerInstanceIndex];
				OnActiveNodeChanged(ShowInstance.ActivePath, HasContinuousPrevStep() ?
					TreeInstance->DebuggerSteps[ActiveStepIndex - 1].InstanceStack[DebuggerInstanceIndex].ActivePath :
					TArray<uint16>());

				UpdateAssetFlags(ShowInstance, RootNode.Get(), ActiveStepIndex);
			}
		}*/
	}
}

void FAdventurePluginDialogDebugger::Setup(UDialogGraph* InDialogAsset, TSharedRef<FAdventurePluginDialogEditor> InEditorOwner)
{
	EditorOwner = InEditorOwner;
	DialogAsset = InDialogAsset;
	/*DebuggerInstanceIndex = INDEX_NONE;
	ActiveStepIndex = 0;
	LastValidStepId = INDEX_NONE;
	ActiveBreakpoints.Reset();
	KnownInstances.Reset();

	CacheRootNode();

#if USE_BEHAVIORTREE_DEBUGGER
	if (IsPIESimulating())
	{
		OnBeginPIE(GEditor->bIsSimulatingInEditor);

		Refresh();
	}
#endif*/
}


void FAdventurePluginDialogDebugger::Tick(float DeltaTime)
{
	if (DialogAsset == NULL || IsPlaySessionPaused())
	{
		return;
	}

	//if (!TreeInstance.IsValid())
	//{
	//	// clear state when active tree is lost
	//	if (DebuggerInstanceIndex != INDEX_NONE)
	//	{
	//		ClearDebuggerState();
	//	}

	//	return;
	//}

#if USE_BEHAVIORTREE_DEBUGGER
	TArray<uint16> EmptyPath;

	int32 TestStepIndex = 0;
	for (int32 Idx = TreeInstance->DebuggerSteps.Num() - 1; Idx >= 0; Idx--)
	{
		const FBehaviorTreeExecutionStep& Step = TreeInstance->DebuggerSteps[Idx];
		if (Step.StepIndex == LastValidStepId)
		{
			TestStepIndex = Idx;
			break;
		}
	}

	// find index of previously displayed state and notify about all changes in between to give breakpoints a chance to trigger
	for (int32 i = TestStepIndex; i < TreeInstance->DebuggerSteps.Num(); i++)
	{
		const FBehaviorTreeExecutionStep& Step = TreeInstance->DebuggerSteps[i];
		if (Step.StepIndex > DisplayedStepIndex)
		{
			ActiveStepIndex = i;
			LastValidStepId = Step.StepIndex;

			UpdateDebuggerInstance();
			UpdateAvailableActions();

			if (DebuggerInstanceIndex != INDEX_NONE)
			{
				UpdateDebuggerViewOnStepChange();

				const FBehaviorTreeDebuggerInstance& ShowInstance = TreeInstance->DebuggerSteps[ActiveStepIndex].InstanceStack[DebuggerInstanceIndex];
				OnActiveNodeChanged(ShowInstance.ActivePath, HasContinuousPrevStep() ?
					TreeInstance->DebuggerSteps[ActiveStepIndex - 1].InstanceStack[DebuggerInstanceIndex].ActivePath :
					EmptyPath);
			}
		}

		// skip rest of them if breakpoint hit
		if (IsPlaySessionPaused())
		{
			break;
		}
	}

	UpdateDebuggerInstance();
	if (DebuggerInstanceIndex != INDEX_NONE)
	{
		const FBehaviorTreeDebuggerInstance& ShowInstance = TreeInstance->DebuggerSteps[ActiveStepIndex].InstanceStack[DebuggerInstanceIndex];

		if (DisplayedStepIndex != TreeInstance->DebuggerSteps[ActiveStepIndex].StepIndex)
		{
			UpdateAssetFlags(ShowInstance, RootNode.Get(), ActiveStepIndex);
		}

		// collect current runtime descriptions for every node
		TArray<FString> RuntimeDescriptions;
		TreeInstance->StoreDebuggerRuntimeValues(RuntimeDescriptions, ShowInstance.RootNode, DebuggerInstanceIndex);

		UpdateAssetRuntimeDescription(RuntimeDescriptions, RootNode.Get());
	}

	UpdateDebuggerViewOnTick();
#endif
}

bool FAdventurePluginDialogDebugger::IsTickable() const
{
	return IsDebuggerReady();
}

void FAdventurePluginDialogDebugger::OnBeginPIE(const bool bIsSimulating)
{
	bIsPIEActive = true;
	if (EditorOwner.IsValid())
	{
		TSharedPtr<FAdventurePluginDialogEditor> EditorOwnerPtr = EditorOwner.Pin();
		EditorOwnerPtr->RegenerateMenusAndToolbars();
		EditorOwnerPtr->DebuggerUpdateGraph();
	}

	/*ActiveBreakpoints.Reset();
	CollectBreakpointsFromAsset(RootNode.Get());

	FindMatchingTreeInstance();*/

	// remove these delegates first as we can get multiple calls to OnBeginPIE()
	/*USelection::SelectObjectEvent.RemoveAll(this);
	FBehaviorTreeDelegates::OnTreeStarted.RemoveAll(this);
	FBehaviorTreeDelegates::OnDebugSelected.RemoveAll(this);

	USelection::SelectObjectEvent.AddRaw(this, &FBehaviorTreeDebugger::OnObjectSelected);
	FBehaviorTreeDelegates::OnTreeStarted.AddRaw(this, &FBehaviorTreeDebugger::OnTreeStarted);
	FBehaviorTreeDelegates::OnDebugSelected.AddRaw(this, &FBehaviorTreeDebugger::OnAIDebugSelected);*/
}

void FAdventurePluginDialogDebugger::OnEndPIE(const bool bIsSimulating)
{
	bIsPIEActive = false;
	if (EditorOwner.IsValid())
	{
		EditorOwner.Pin()->RegenerateMenusAndToolbars();
	}

	//USelection::SelectObjectEvent.RemoveAll(this);
	//FBehaviorTreeDelegates::OnTreeStarted.RemoveAll(this);
	//FBehaviorTreeDelegates::OnDebugSelected.RemoveAll(this);

	/*ClearDebuggerState();
	ActiveBreakpoints.Reset();

	FBehaviorTreeDebuggerInstance EmptyData;
	UpdateAssetFlags(EmptyData, RootNode.Get(), INDEX_NONE);
	UpdateDebuggerViewOnInstanceChange();*/
}

void FAdventurePluginDialogDebugger::OnPausePIE(const bool bIsSimulating)
{
}

void FAdventurePluginDialogDebugger::StopPlaySession()
{
	if (GUnrealEd->PlayWorld)
	{
		GEditor->RequestEndPlayMap();
	}
}

void FAdventurePluginDialogDebugger::PausePlaySession()
{
	if (GUnrealEd->PlayWorld && !GUnrealEd->PlayWorld->bDebugPauseExecution)
	{
		GUnrealEd->PlayWorld->bDebugPauseExecution = true;
		GUnrealEd->PlaySessionPaused();
	}
}

void FAdventurePluginDialogDebugger::ResumePlaySession()
{
	if (GUnrealEd->PlayWorld && GUnrealEd->PlayWorld->bDebugPauseExecution)
	{
		GUnrealEd->PlayWorld->bDebugPauseExecution = false;
		GUnrealEd->PlaySessionResumed();
	}
}

bool FAdventurePluginDialogDebugger::IsPlaySessionPaused()
{
	return GUnrealEd->PlayWorld && GUnrealEd->PlayWorld->bDebugPauseExecution;
}

bool FAdventurePluginDialogDebugger::IsPlaySessionRunning()
{
	return GUnrealEd->PlayWorld && !GUnrealEd->PlayWorld->bDebugPauseExecution;
}

bool FAdventurePluginDialogDebugger::IsPIESimulating()
{
	return GEditor->bIsSimulatingInEditor || GEditor->PlayWorld;
}

bool FAdventurePluginDialogDebugger::IsPIENotSimulating()
{
	return !GEditor->bIsSimulatingInEditor && (GEditor->PlayWorld == NULL);
}


bool FAdventurePluginDialogDebugger::IsDebuggerReady() const
{
	return bIsPIEActive;
}


#undef LOCTEXT_NAMESPACE