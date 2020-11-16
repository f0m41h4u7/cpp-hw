#!/bin/bash

build=$1

build_number=$TRAVIS_BUILD_NUMBER

if [[ -z $build_number ]]; then
  build_number=1
fi

TRAVIS_BUILD_NUMBER=$build_number cmake $(pwd)

if [[ $build == deb ]]; then
  cmake --build $(pwd)
  cmake --build $(pwd) --target package
  curl -T $TRAVIS_BRANCH-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -uf0m41h4u7:$BINTRAY_API_KEY "https://api.bintray.com/content/f0m41h4u7/cpp-hw/$TRAVIS_BRANCH/$TRAVIS_BUILD_NUMBER/$TRAVIS_BRANCH-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"
elif [[ $build == test ]]; then
  cmake --build $(pwd)
  cmake --build $(pwd) --target test
  ./test
fi
