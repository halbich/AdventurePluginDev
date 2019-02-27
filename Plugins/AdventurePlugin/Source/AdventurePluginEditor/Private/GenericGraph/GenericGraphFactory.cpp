/*
This file is based on a third party plugin called Generic Graph Editor,
created by jinyuliao, which is distributed under MIT license and is available
here: https://github.com/jinyuliao/GenericGraph. See LICENSE file in this folder.
*/

#include "GenericGraph/GenericGraphFactory.h"
#include "GenericGraph/GenericGraph.h"

#define LOCTEXT_NAMESPACE "GenericGraphFactory"

UGenericGraphFactory::UGenericGraphFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UGenericGraph::StaticClass();
}

UGenericGraphFactory::~UGenericGraphFactory()
{

}

UObject* UGenericGraphFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
}

#undef LOCTEXT_NAMESPACE
