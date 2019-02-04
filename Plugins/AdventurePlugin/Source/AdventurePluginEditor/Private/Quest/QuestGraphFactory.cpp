#include "Quest/QuestGraphFactory.h"
#include "AdventurePluginRuntime/Public/Quest/Graph/QuestGraph.h"

#define LOCTEXT_NAMESPACE "DialogGraphFactory"

UQuestGraphFactory::UQuestGraphFactory()
{
	SupportedClass = UQuestGraph::StaticClass();
}

UQuestGraphFactory::~UQuestGraphFactory()
{

}

#undef LOCTEXT_NAMESPACE
