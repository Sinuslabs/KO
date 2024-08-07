source ../info.env

project=$NAME
script_root=$PWD
project_root=$PROJECT_ROOT
OS="MacOS"

# Confirm all required variables are set
if [ -z "$NAME" ] || [ -z "$VERSION" ] || [ -z "$USERNAME" ] || [ -z "$PASSWORD" ] || [ -z "$UPLOAD_LOCATION" ]; then
    echo "Error: One or more required variables are not set."
    exit 1
fi

echo "Uploading to Storage ..."
curl --progress-bar -k -u "${USERNAME}:${PASSWORD}" -T "${project_root}/build/${OS}/${NAME}.pkg" "${UPLOAD_LOCATION}/builds/${NAME}/${VERSION}/${NAME}-MacOS.pkg"

