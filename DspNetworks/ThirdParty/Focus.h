
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::focus_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Focus/Focus.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Focus/Focus.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Focus/FocusProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::focus_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Focus, focus_ns);

}  // namespace project
