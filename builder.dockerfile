FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y ruby
RUN apt-get install -y build-essential zip unzip jq curl cmake
RUN gem install bundler:1.17.3

WORKDIR /build
COPY Gemfile .
COPY Gemfile.lock .
RUN bundle install
