#pragma once

#include "CoreMinimal.h"
#include "Logging/MessageLog.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules
 * within this plugin.
 */
class IAdventurePluginRuntime : public IModuleInterface
{
public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IAdventurePluginRuntime& Get()
	{
		return FModuleManager::LoadModuleChecked< IAdventurePluginRuntime >("AdventurePluginRuntime");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("AdventurePluginRuntime");
	}
};

/**
* Logs the specific warning to the message log.
* @param Message The text of the warning.
*/
#define LOG_Warning(Message) \
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1,5, FColor::Yellow, *Message.ToString()); \
	FMessageLog("AdventurePluginLog").Warning(Message);

/**
* Logs the specific error to the message log.
* @param Message The text of the error.
*/
#define LOG_Error(Message) \
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1,5, FColor::Red, *Message.ToString()); \
	FMessageLog("AdventurePluginLog").Error(Message);


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)