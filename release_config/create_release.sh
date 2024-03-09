#!/bin/bash

RELEASE_TO_CREATE="$1"
SHA_PGKBUILD_LINE=12
GIT_USERNAME="$2"
GIT_PASSWORD="$3"

cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

create_lib_release(){
    local RELEASE_NAME=libtempli_archlinuxi@@TEMPLI_LIB_VERSION@
    mkdir -p "${RELEASE_NAME}"
    mkdir -p "${RELEASE_NAME}/lib"
    mkdir -p "${RELEASE_NAME}/include"
    mkdir -p "${RELEASE_NAME}/lib/cmake"
    mkdir -p "$release/lib/cmake"
    
    cp -r build/lib "${RELEASE_NAME}/lib"
    cp -r build/cmake "${RELEASE_NAME}/lib/cmake/rcli"
    cp -r include/Templi "${RELEASE_NAME}/include/Templi"
    
    # create tar release and configure hash
    tar -czvf "release/${RELEASE_NAME.tar.gz}" "${RELEASE_NAME}"
    hash_value=$(sha256sum "release/$RELEASE_NAME" | awk '{print $1}')
    new_shaline="sha256sums=(\"${hash_value}\")"
    sed -i "${SHA_PGKBUILD_LINE}s/.*/${new_shaline}/" "PKGBUILD/lib/PKGBUILD"
}

if [ "$RELEASE_TO_CREATE" == "LIB"]; then
    create_lib_release
fi
