
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::pressure5_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Pressure5/Pressure5.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Pressure5/Pressure5.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Pressure5/Pressure5Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pressure5_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Pressure5, pressure5_ns);

}  // namespace project
