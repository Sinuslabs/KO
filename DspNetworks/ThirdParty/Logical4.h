
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::logical4_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Logical4/Logical4.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Logical4/Logical4.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Logical4/Logical4Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::logical4_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Logical4, logical4_ns);

}  // namespace project
