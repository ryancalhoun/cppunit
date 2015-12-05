#!/bin/bash

set -e

cd "$(cd "$(dirname "$0")"; pwd)"
cat include/cppunit/Portability.h | grep CPPUNIT_VERSION | grep -o "[0-9.]\+"
