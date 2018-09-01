#include "DialogGraphFactory.h"
#include "AdventurePluginRuntime/Public/Dialogue/Graph/DialogGraph.h"

#define LOCTEXT_NAMESPACE "DialogGraphFactory"

UDialogGraphFactory::UDialogGraphFactory()
{
	SupportedClass = UDialogGraph::StaticClass();
}

UDialogGraphFactory::~UDialogGraphFactory()
{

}

/*
UObject* UGenericGraphFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
}
*/

#undef LOCTEXT_NAMESPACE
