
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::mojo_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Mojo/Mojo.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Mojo/Mojo.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Mojo/MojoProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::mojo_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Mojo, mojo_ns);

}  // namespace project
