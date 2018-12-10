#include "skse64/PluginAPI.h"		// super
#include "skse64_common/skse_version.h"	// What version of SKSE is running?
#include <shlobj.h>				// CSIDL_MYCODUMENTS

#include "SimplyKnock.h"

static PluginHandle					g_pluginHandle = kPluginHandle_Invalid;
static SKSEPapyrusInterface         * g_papyrus = NULL;

extern "C"	{

	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)	{	// Called by SKSE to learn about this plugin and check that it's safe to load it
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\SimplyKnock.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("SimplyKnockSKSE");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		"SimplyKnock";
		info->version =		1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = skse->GetPluginHandle();

		if(skse->isEditor)
		{
			_MESSAGE("loaded in editor, marking as incompatible");

			return false;
		}
		if (skse->runtimeVersion != CURRENT_RELEASE_RUNTIME)
		{
			_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);
			return false;
		}
		if (skse->runtimeVersion != RUNTIME_VERSION_1_5_62)
		{
			_MESSAGE("This plugin is not compatible with this versin of game.");
			return false;
		}

		// ### do not do anything else in this callback
		// ### only fill out PluginInfo and return true/false

		// supported runtime version
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)	{	// Called by SKSE to load this plugin
		_MESSAGE("SimplyKnock loaded");

		g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);

		//Check if the function registration was a success...
		bool btest = g_papyrus->Register(SimplyKnockNamespace::RegisterFuncs);

		if (btest) {
			_MESSAGE("Register Succeeded");
		}

		return true;
	}

};
