#!/bin/bash

os=$(uname -s | tr 'A-Z' 'a-z')
arch=$(uname -m)

cd dist
tar czf cppunit-$os-$arch.tgz cppunit
