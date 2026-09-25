#!/usr/bin/env bash
# Builds the GitHub release files into dist/ (same names and layout as the previous releases,
# which PKGBUILD/cli and PKGBUILD/lib download):
#
#   templi-cli-linux-x86_64@<version>.tar.gz   bin/templi (static binary)
#   templi-lib-linux-x86_64@<version>.tar.gz   include/Templi, lib/libTempli.a, lib/cmake/Templi
#
# The version comes from `project(... VERSION x)` in CMakeLists.txt.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"

version=$(sed -n 's/^project(templi_tools VERSION \([0-9.]*\))$/\1/p' CMakeLists.txt)
[ -n "$version" ] || { echo "cannot read the version from CMakeLists.txt" >&2; exit 1; }
cli="templi-cli-linux-x86_64@${version}"
lib="templi-lib-linux-x86_64@${version}"
dist="$root/dist"
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT

echo "packaging Templi v${version}"

# configuring regenerates the PKGBUILDs with a placeholder checksum: keep the current ones
cp -r PKGBUILD "$work/PKGBUILD.saved"
cmake -S . -B "$work/build" -DCMAKE_BUILD_TYPE=Release -DTEMPLI_BUILD_TESTS=OFF \
	-DCMAKE_INSTALL_LIBDIR=lib >/dev/null
rm -rf PKGBUILD && cp -r "$work/PKGBUILD.saved" PKGBUILD
cmake --build "$work/build" --parallel
cmake --install "$work/build" --prefix "$work/install" >/dev/null

"$work/install/bin/templi" --version >/dev/null

rm -rf "$dist"
mkdir -p "$dist" "$work/$cli" "$work/$lib"
cp -r "$work/install/bin" "$work/$cli/"
cp -r "$work/install/include" "$work/install/lib" "$work/$lib/"

(cd "$work" && tar -czf "$dist/$cli.tar.gz" "$cli" && tar -czf "$dist/$lib.tar.gz" "$lib")
(cd "$dist" && sha256sum -- * >SHA256SUMS)

echo "release files in dist/:"
(cd "$dist" && ls -1)
