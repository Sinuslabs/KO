#!/bin/bash -eu

# Load environment variables
source ../info.env
source ./.env

# Variables for reuse
signing_identity="Developer ID Application: $APPLE_TEAM_ID"
installer_identity="Developer ID Installer: $APPLE_TEAM_ID"
keychain_profile="SinusLabsNotarization"
script_root=$PWD
project_root=$PROJECT_ROOT

# Temporary directories for package contents
vst3_temp=$(mktemp -d)
au_temp=$(mktemp -d)

# Function to sign binaries
sign_binary() {
  local path="$1"
  echo "Signing $path"
  codesign --deep --force --verbose --timestamp --sign "$signing_identity" "$path"
}

# Function to build package
build_pkg() {
  local root="$1"
  local plist="$2"
  local identifier="$3"
  local install_location="$4"
  local output_pkg="$5"

  echo "Building $output_pkg"
  pkgbuild --root "$root" --component-plist "$plist" --identifier "$identifier" --version "$VERSION" --install-location "$install_location" "$output_pkg"
}

# Copy the binaries
cp -R "$project_root/Binaries/Builds/MacOSX/build/Release/$NAME.vst3" "$vst3_temp"
cp -R "$project_root/Binaries/Builds/MacOSX/build/Release/$NAME.component" "$au_temp"

# Sign binaries
sign_binary "$vst3_temp/$NAME.vst3/Contents/MacOS/$NAME"
sign_binary "$au_temp/$NAME.component/Contents/MacOS/$NAME"

# Generate component plists
pkgbuild --analyze --root "$vst3_temp/$NAME.vst3/Contents" "./Info-VST3.plist"
pkgbuild --analyze --root "$au_temp/$NAME.component/Contents" "./Info-AU.plist"

# Build packages
build_pkg "$vst3_temp" "./Info-VST3.plist" "com.sinuslabs.pkg.$NAME.VST3" "/Library/Audio/Plug-Ins/VST3" "${NAME}_VST3.pkg"
build_pkg "$au_temp" "./Info-AU.plist" "com.sinuslabs.pkg.$NAME.AU" "/Library/Audio/Plug-Ins/Components" "${NAME}_AU.pkg"

# Create final product package
echo "Building product package"
productbuild --distribution "./Distribution.xml" --package-path "./" --resources "./Resources" --sign "$installer_identity" "${NAME}-MacOS.pkg"

# Cleanup temporary files
rm -f "Info-VST3.plist" "Info-AU.plist"
rm -rf "$vst3_temp" "$au_temp"

# Sign the final package
echo "Signing the final package"
productsign --sign "$installer_identity" "${NAME}-MacOS.pkg" "${NAME}-MacOS-signed.pkg"

# Notarize the package
echo "Submitting package for notarization"
xcrun notarytool submit "./${NAME}-MacOS-signed.pkg" --keychain-profile "$keychain_profile" --wait

# Staple notarization ticket
echo "Stapling notarization ticket"
xcrun stapler staple "./${NAME}-MacOS-signed.pkg"

# Verify final package
echo "Verifying the final package"
spctl --assess --type install --verbose "./${NAME}-MacOS-signed.pkg"

rm -rf "${NAME}-MacOS.pkg"
rm -rf "${NAME}_AU.pkg"
rm -rf "${NAME}_VST3.pkg"
mv "${NAME}-MacOS-signed.pkg" "${NAME}-MacOS.pkg"
