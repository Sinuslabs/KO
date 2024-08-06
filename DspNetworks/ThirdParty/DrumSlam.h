
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::drumslam_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/DrumSlam/DrumSlam.h"

#include "../../External/airwindows/plugins/LinuxVST/src/DrumSlam/DrumSlam.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/DrumSlam/DrumSlamProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::drumslam_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(DrumSlam, drumslam_ns);

}  // namespace project
