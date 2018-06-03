// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventurePluginEdModeToolkit.h"
#include "AdventurePluginEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/LevelScriptBlueprint.h"
#include "EdGraph/EdGraphNode.h"

#include "EdGraphSchema_K2.h"
#include "K2Node_CallFunction.h"
#include "BlueprintGraphClasses.h"
#include "K2Node.h"
#include "K2Node_CallFunction.h"

#include "KismetCompiler.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "BlueprintEditor.h"

#include "AdventurePluginEditor.h"

#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FAdventurePluginEdModeToolkit"

FAdventurePluginEdModeToolkit::FAdventurePluginEdModeToolkit()
{
}

void FAdventurePluginEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}

		static FReply OnButtonClick(FVector InOffset)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AActor* LevelActor = Cast<AActor>(*Iter))
				{
					// Register actor in opened transaction (undo/redo)
					LevelActor->Modify();
					// Move actor to given location
					LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
				}
			}

			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}

		static FReply OnAdventurePluginButtonClick()
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("AdventurePluginActorsTransactionName", "AdventurePlugin Button"));

			// For each selected actor

			auto world = GEditor->GetEditorWorldContext().World();
			if (!world)
			{
				GEditor->EndTransaction();
				return FReply::Handled();
			}

			// Iterate over all levels, and try to find a matching function on the level's script actor
			for (TArray<ULevel*>::TConstIterator it = world->GetLevels().CreateConstIterator(); it; ++it)
			{
				ULevel* CurLevel = *it;
				if (CurLevel && CurLevel->bIsVisible)
				{
					GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, CurLevel->GetName());
					ALevelScriptActor* LSA = CurLevel->GetLevelScriptActor();
					if (LSA)
					{
						GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, LSA->GetName());
						//// Find an event with no parameters
						//UFunction* EventTarget = LSA->FindFunction(EventName);
						//if (EventTarget && EventTarget->NumParms == 0)
						//{
						//	LSA->ProcessEvent(EventTarget, NULL);
						//	bFoundEvent = true;
						//}


					}

					auto lsb = CurLevel->LevelScriptBlueprint;

					if (lsb)
					{




						TArray<UEdGraph*> AllGraphs;
						lsb->GetAllGraphs(AllGraphs);

						for (TArray<UEdGraph*>::TConstIterator it(AllGraphs); it; ++it)
						{
							UEdGraph* CurrentGraph = *it;

							if (CurrentGraph != nullptr) {
								GEngine->AddOnScreenDebugMessage(0, 10, FColor::Yellow, CurrentGraph->GetName());

								auto fn = CurrentGraph->CreateIntermediateNode<UK2Node_CallFunction>();

								CurrentGraph->AddNode(fn);
							}
						}
					}
				}
			}



			ALevelScriptActor* lsa = world->GetLevelScriptActor();

			if (lsa)
			{
				if (ULevelScriptBlueprint* MyBlueprint = Cast<ULevelScriptBlueprint>(lsa->GetClass()->ClassGeneratedBy))
				{
					for (auto g : MyBlueprint->EventGraphs)
					{
						GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, g->GetName());
					}

					//MyBlueprint->
					//MyBlueprint->SetObjectBeingDebugged(NULL);
				}
			}


			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}

		static FReply OnAdventurePluginButtonClick1()
		{
			FAdventurePluginEditor& e = FAdventurePluginEditor::Get();

			e.Log(EMessageSeverity::Type::Warning, FText::FromString(TEXT("Debug log. Remove me ASAP")));

			return FReply::Handled();
		}

		static TSharedRef<SWidget> MakeButton(FText InLabel, const FVector InOffset)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnButtonClick, InOffset);
		}

		static TSharedRef<SWidget> MakeAdventurePluginButton(FText InLabel)
		{
			return SNew(SButton)
				.Text(InLabel)
				.OnClicked_Static(&Locals::OnAdventurePluginButtonClick1);
		}
	};

	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)
		.Padding(25)
		.IsEnabled_Static(&Locals::IsWidgetEnabled)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		.Padding(50)
		[
			SNew(STextBlock)
			.AutoWrapText(true)
		.Text(LOCTEXT("HelperLabel", "Select some actors and move them around using buttons below"))
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.AutoHeight()
		[
			Locals::MakeButton(LOCTEXT("UpButtonLabel", "Up"), FVector(0, 0, Factor))
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			Locals::MakeButton(LOCTEXT("LeftButtonLabel", "Left"), FVector(0, -Factor, 0))
		]
	+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			Locals::MakeButton(LOCTEXT("RightButtonLabel", "Right"), FVector(0, Factor, 0))
		]
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.AutoHeight()
		[
			Locals::MakeButton(LOCTEXT("DownButtonLabel", "Down"), FVector(0, 0, -Factor))
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.AutoHeight()
		[
			Locals::MakeAdventurePluginButton(LOCTEXT("AdventurePluginButtonLabel", "AdventurePlugin"))
		]

		];

	FModeToolkit::Init(InitToolkitHost);
}

FName FAdventurePluginEdModeToolkit::GetToolkitFName() const
{
	return FName("AdventurePluginEdMode");
}

FText FAdventurePluginEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("AdventurePluginEdModeToolkit", "DisplayName", "AdventurePluginEdMode Tool");
}

class FEdMode* FAdventurePluginEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FAdventurePluginEdMode::EM_AdventurePluginEdModeId);
}

#undef LOCTEXT_NAMESPACE
