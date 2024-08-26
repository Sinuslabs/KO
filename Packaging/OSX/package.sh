#!/bin/bash -eu

source ../info.env
source ./.env

script_root=$PWD
project_root=$PROJECT_ROOT

mkdir au/
cp -R "$project_root/Binaries/Builds/MacOSX/build/Release/$NAME.component" au

mkdir vst3/
cp -R "$project_root/Binaries/Builds/MacOSX/build/Release/$NAME.vst3" vst3

pkgbuild --analyze --root "$project_root/Binaries/Builds/MacOSX/build/Release/$NAME.vst3/Contents" "./Info-VST3.plist"

pkgbuild --analyze --root "$project_root/Binaries/Builds/MacOSX/build/Release/$NAME.component/Contents" "./Info-AU.plist"

pkgbuild --root "./vst3/" --component-plist "./Info-VST3.plist" --identifier "com.sinuslabs.pkg.KO.VST3" --version $VERSION --install-location "/Library/Audio/Plug-Ins/VST3" "${NAME}_VST3.pkg"

pkgbuild --root "./au/" --component-plist "./Info-AU.plist" --identifier "com.sinuslabs.pkg.KO.AU" --version $VERSION --install-location "/Library/Audio/Plug-Ins/Components" "${NAME}_AU.pkg"

productbuild --distribution "./Distribution.xml" --package-path "./" --resources "./Resources" --sign "Developer ID Installer: ${APPLE_TEAM_ID}" "${NAME}-MacOS.pkg"

rm "Info-VST3.plist"
rm "Info-AU.plist"
rm "${NAME}_VST3.pkg"
rm "${NAME}_AU.pkg"
rm -r "./vst3"
rm -r "./au"