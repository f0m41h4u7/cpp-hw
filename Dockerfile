FROM gcc:10.2.0

ARG PROJECT

WORKDIR /app

RUN apt-get update && apt-get -y upgrade && apt-get install -y curl bash make cmake libboost-test-dev doxygen \
    && echo "deb http://archive.ubuntu.com/ubuntu xenial main universe" | tee -a /etc/apt/sources.list

ADD ./$PROJECT .

ENTRYPOINT ["./build.sh"]
