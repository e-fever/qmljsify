FROM node:10.15.3-alpine

MAINTAINER Ben Lau version: 0.1

VOLUME /data

RUN apk add --update --no-cache bash \
    alpine-sdk qt5-qtbase-dev qt5-qtbase-dev qt5-qtdeclarative qt5-qtquickcontrols2-dev go && \
    rm -rf /var/cache/apk/* && \
    npm install -g webpack@3.10.0 && \
    go get qpm.io/qpm && cp /root/go/bin/qpm /usr/bin && rm -rf /root/go

ADD app/qmljsify /src

RUN export PATH=/usr/lib/qt5/bin:$PATH && cd /src && qpm install && qmake && make && cp qmljsify /usr/bin && make clean

ADD docker/wrapper.sh /usr/bin/wrapper.sh
RUN chmod a+x /usr/bin/wrapper.sh

ENTRYPOINT ["/usr/bin/wrapper.sh"]
