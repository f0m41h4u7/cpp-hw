FROM gcc:10.2.0

ARG PROJECT

WORKDIR /app

RUN apt-get update && apt-get -y upgrade && \
    apt-get install -y bash make cmake libboost-test-dev doxygen libgtest-dev libboost-system-dev tao-pegtl-dev libboost-dev && \
    echo "deb http://archive.ubuntu.com/ubuntu xenial main universe" | tee -a /etc/apt/sources.list

ADD ./$PROJECT .

ENTRYPOINT ["./build.sh"]
