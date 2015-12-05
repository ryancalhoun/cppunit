#!/bin/bash

set -e

cd "$(cd "$(dirname "$0")"; pwd)"

os=$(uname -s | tr 'A-Z' 'a-z')
arch=$(uname -m)

cd dist
if [[ "$CC" = "" ]]; then
	tar czf cppunit-$os-$arch.tgz cppunit
else
	tar czf cppunit-$os-$arch-$CC.tgz cppunit
fi
