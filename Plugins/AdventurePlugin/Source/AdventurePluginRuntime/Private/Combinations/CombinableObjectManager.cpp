#include "CombinableObjectManager.h"
#include "AdventurePluginRuntime.h"

#pragma optimize("", off)
UCombinableObject* UCombinableObjectManager::GetObject(TSubclassOf<UCombinableObject> Object)
{
	if (Object == nullptr)
	{
		LOG_Warning(NSLOCTEXT("AP", "getObjectNull", "CombinableObjectManager::GetObject - Object is NULL."));
		return nullptr;
	}
	if (Object->HasAnyClassFlags(CLASS_Abstract))
	{
		LOG_Warning(NSLOCTEXT("AP", "getItemAbstract", "CombinableObjectManager::GetObject - Object is abstract."));
		return nullptr;
	}
	auto* toReturn = Objects.Find(Object);
	if (toReturn == nullptr || *toReturn == nullptr || !(*toReturn)->IsValidLowLevel())
	{
		RegisterObject(Object);
		toReturn = Objects.Find(Object);
	}
	check(toReturn && *toReturn && "Item instance should never be null");
	return toReturn ? *toReturn : nullptr;
}

void UCombinableObjectManager::RegisterObject(TSubclassOf<UCombinableObject> ObjectClass)
{
	UCombinableObject* newObject = NewObject<UCombinableObject>(this, ObjectClass);
	newObject->Init();
	check(newObject != nullptr && "It should always be possible to instantiate a combinable object");
	Objects.Add(ObjectClass, newObject);
}
#pragma optimize("", on)