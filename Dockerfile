FROM alpine:edge

ARG PROJECT

WORKDIR /app

RUN apk update && apk upgrade && apk add --no-cache build-base curl bash gcc g++ make cmake boost-dev 

ADD ./$PROJECT .

ENTRYPOINT ["./build.sh"]
