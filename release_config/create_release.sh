#!/bin/bash

GIT_USERNAME="$1"
GIT_PASSWORD="$2"
RELEASE_TO_CREATE="$3"

SHA_PGKBUILD_LINE=12

cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cd build 
make
cd ..
mkdir -p release
cd release

create_tar_release(){
    local RELEASE_NAME="$1"
    local PKGBUILD_PATH="$2"

    # create tar release and configure hash
    tar -czvf "${RELEASE_NAME}.tar.gz" "${RELEASE_NAME}"
    hash_value=$(sha256sum "${RELEASE_NAME}.tar.gz" | awk '{print $1}')
    new_shaline="sha256sums=(\"${hash_value}\")"
    sed -i "${SHA_PGKBUILD_LINE}s/.*/${new_shaline}/" "${PKGBUILD_PATH}" 
}

create_lib_release(){
    local RELEASE_NAME=libtempli_archlinux@@TEMPLI_LIB_VERSION@
    mkdir -p "${RELEASE_NAME}"
    mkdir -p "${RELEASE_NAME}/lib"
    mkdir -p "${RELEASE_NAME}/include"
    mkdir -p "${RELEASE_NAME}/lib/cmake"
    
    cp -r ../build/lib "${RELEASE_NAME}"
    cp -r ../build/cmake "${RELEASE_NAME}/lib/cmake/Templi"
    cp -r ../include/Templi "${RELEASE_NAME}/include/Templi"

    create_tar_release "${RELEASE_NAME}" "../PKGBUILD/lib/PKGBUILD"
}

create_cli_release(){
    local RELEASE_NAME=templi_cli_archlinux@@TEMPLI_LIB_VERSION@
    mkdir -p "${RELEASE_NAME}"
    mkdir -p "${RELEASE_NAME}/bin"

    cp -r ../build/bin "${RELEASE_NAME}"

    create_tar_release "${RELEASE_NAME}" "../PKGBUILD/cli/PKGBUILD"
}

create_qt_release(){
    echo "..."
}

for arg in "$@"; do
    case "$arg" in
        "LIB")
            create_lib_release
            ;;
        "CLI")
            create_cli_release
            ;;
        "QT")
            echo "L'argument est égal à string3."
            ;;
        *)
            ;;
    esac
done
