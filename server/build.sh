#!/bin/bash

build=$1
build_number=$TRAVIS_BUILD_NUMBER

if [[ -z $build_number ]]; then
  build_number=1
fi

set -xeuo pipefail

TRAVIS_BUILD_NUMBER=$build_number cmake $(pwd)

if [[ $build == deb ]]; then
  cmake $(pwd)
  make async
  make install
  make server
  make package
fi
