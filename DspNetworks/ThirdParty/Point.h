
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::point_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Point/Point.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Point/Point.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Point/PointProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::point_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Point, point_ns);

}  // namespace project
