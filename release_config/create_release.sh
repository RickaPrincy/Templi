#!/bin/bash

RELEASE_TO_CREATE="$1"
GIT_URL="$2"

SHA_PGKBUILD_LINE=12
release_path=()

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
    release_path+=("${RELEASE_NAME}")
    
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
    release_path+=("${RELEASE_NAME}")

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

TAG_NAME=v@TEMPLI_VERSION@
git add --all
git commit -m "feat: templi@@TEMPLI_VERSION@"
git config --global user.name "\"RickaPrincy\""; 
git config --global user.email "\"rckprincy@gmail.com\""; 
git remote add origin "${GIT_URL}"
git push origin -u main

git tag -a  -m "Templi ${TAG_NAME}" 
git push origin v@TEMPLI_VERSION@

# create release
response=$(curl -s -X POST -u "RickaPrincy" https://api.github.com/repos/RickaPrincy/Templi/releases \
    -d "{\"tag_name\":\"$TAG_NAME\",\"name\":\"$TAG_NAME\",\"draft\":false,\"prerelease\":false}")

release_id=$(echo "$response" | jq -r '.id')

for file in "${release_path[@]}"; do
    filename=$(basename "$file")
    curl -X POST -u "RickaPrincy" -H "Content-Type: $(file -b --mime-type "$file")" \
        --data-binary "@$file" \
        "https://uploads.github.com/repos/RickaPrincy/Templi/releases/$release_id/assets?name=$filename"
done
