/** Autogenerated Main.cpp. */

// ===============================| Include only the DSP files  |===============================

#include <AppConfig.h>
#include <hi_dsp_library/hi_dsp_library.h>
#include <hi_faust/hi_faust.h>
#include "includes.h"
// =========================| Now we can add the rest of the codebase |=========================

#include <JuceHeader.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"

// =====================================| Project Factory |=====================================

namespace project
{

struct Factory: public scriptnode::dll::StaticLibraryHostFactory
{
	Factory()
	{
		TempoSyncer::initTempoData();
		// Node registrations -----------------------------------------------------------------
		
		registerPolyNode<project::Tube2<1>, project::Tube2<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::Transient<1>, project::Transient<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::Point<1>, project::Point<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::Mojo<1>, project::Mojo<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::Focus<1>, project::Focus<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::ClipSoftly<1>, project::ClipSoftly<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::Boxer<1>, wrap::illegal_poly<project::Boxer<1>>>();
		registerPolyNode<project::Karate<1>, wrap::illegal_poly<project::Karate<1>>>();
		registerPolyNode<project::Sumo<1>, wrap::illegal_poly<project::Sumo<1>>>();
	}
};
}

project::Factory f;

// =================================| Exported DLL functions |=================================

DLL_EXPORT int getNumNodes()
{
	return f.getNumNodes();
}

DLL_EXPORT size_t getNodeId(int index, char* t)
{
	return HelperFunctions::writeString(t, f.getId(index).getCharPointer());
}

DLL_EXPORT bool isThirdPartyNode(int index)
{
	return index < 6;
}

DLL_EXPORT int getNumDataObjects(int nodeIndex, int dataTypeAsInt)
{
	return f.getNumDataObjects(nodeIndex, dataTypeAsInt);
}

DLL_EXPORT void deInitOpaqueNode(scriptnode::OpaqueNode* n)
{
	n->callDestructor();
}

DLL_EXPORT void initOpaqueNode(scriptnode::OpaqueNode* n, int index, bool polyIfPossible)
{
	f.initOpaqueNode(n, index, polyIfPossible);
}
DLL_EXPORT int getHash(int index)
{
	static const int thirdPartyOffset = 6;
	static const int hashIndexes[3] =
	{
		1685608230,
		-1240526098,
		287783095
	};
	return (index >= thirdPartyOffset) ? hashIndexes[index - thirdPartyOffset] : 0;
}
DLL_EXPORT int getWrapperType(int index)
{
	return f.getWrapperType(index);
}
DLL_EXPORT ErrorC getError()
{
	return f.getError();
}
DLL_EXPORT void clearError()
{
	f.clearError();
}
DLL_EXPORT int getDllVersionCounter()
{
	return scriptnode::dll::ProjectDll::DllUpdateCounter;
}

#pragma clang diagnostic pop


