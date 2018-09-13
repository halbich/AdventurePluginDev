#include "Dialogue/DialogGraphFactory.h"
#include "AdventurePluginRuntime/Public/Dialogue/Graph/DialogGraph.h"

#define LOCTEXT_NAMESPACE "DialogGraphFactory"

UDialogGraphFactory::UDialogGraphFactory()
{
	SupportedClass = UDialogGraph::StaticClass();
}

UDialogGraphFactory::~UDialogGraphFactory()
{

}

#undef LOCTEXT_NAMESPACE
