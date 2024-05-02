FROM continuumio/miniconda3:latest

ARG PYTHON_VERSION=3.11.9
ARG MINGW_VERSION=10.2.1-6+24.2
ARG MINGW_BINUTIL_VERSION=2.35-2+8.11
ARG SCONS_VERSION=4.5.2

SHELL ["/bin/bash", "--login", "-c"]

RUN conda init bash

RUN set -ex \
    \
    && conda create -y -n gde python=${PYTHON_VERSION} \
    && conda activate gde \
    && conda install -c conda-forge -y scons=${SCONS_VERSION} \
    && ln -s /opt/conda/envs/gde/bin/python /usr/bin/python-gde

RUN sed -i 's#http://deb.debian.org/#http://mirrors.aliyun.com/#' /etc/apt/sources.list

RUN set -ex \
    \
    && DEBIAN_FRONTEND=noninteractive apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get upgrade --no-install-recommends -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
    \
    build-essential \
    g++-mingw-w64-x86-64=${MINGW_VERSION} \
    binutils-mingw-w64=${MINGW_BINUTIL_VERSION} \
    \
    && apt-get autoremove --purge -y \
    && apt-get clean

RUN source activate gde \
    && python --version \
    && scons --version \
    && x86_64-w64-mingw32-gcc --version
