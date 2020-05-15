FROM ubuntu:18.04
RUN echo "deb http://cz.archive.ubuntu.com/ubuntu eoan main universe" | tee -a  /etc/apt/sources.list \
    && apt-get update \
    && apt-get install -y build-essential \
    && apt-get install -y g++-9 \
    && apt-get install -y libboost-all-dev \
    && apt-get install -y libjsoncpp-dev \
    && apt-get install -y libcurl4-gnutls-dev \
    && apt-get install -y libssl-dev \
    && apt-get install -y libtbb-dev
WORKDIR /Source
