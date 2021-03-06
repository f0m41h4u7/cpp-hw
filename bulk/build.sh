#!/bin/bash

build=$1
build_number=$TRAVIS_BUILD_NUMBER

if [[ -z $build_number ]]; then
  build_number=1
fi

set -xeuo pipefail

TRAVIS_BUILD_NUMBER=$build_number cmake $(pwd)

if [[ $build == deb ]]; then
  cmake --build $(pwd)
  cmake --build $(pwd) --target package
elif [[ $build == test ]]; then
  cmake --build $(pwd)
  cmake --build $(pwd) --target test
  ./test
fi
