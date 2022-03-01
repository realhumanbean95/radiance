# *************** 0x54616e7a6c650001 ***************
# * Tanzle™ Confidential
# * © 2020 Tanzle, Inc. All rights reserved.
# *************** 0x54616e7a6c650001 ***************

# Ubuntu 20.04.3 LTS codename = focal
# FROM ubuntu:focal-20210827
FROM nvidia/cudagl:11.4.0-devel-ubuntu20.04

# setup environment variables
ENV NVIDIA_VISIBLE_DEVICES ${NVIDIA_VISIBLE_DEVICES:-all}
ENV NVIDIA_DRIVER_CAPABILITIES ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}display,graphics,utility
ENV NVIDIA_DRIVER_VERSION 470.86

# set the locale
ENV LC_ALL=C.UTF-8 \
    LANG=C.UTF-8 \
    LANGUAGE=C.UTF-8
 
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive TERM=linux apt-get install -q -y \
        apt-transport-https \
        apt-utils \
        bash-completion \
        build-essential \
        clang-10 \
    && apt-get autoremove -y && apt-get clean && rm -rf /var/lib/apt/lists/*

# install nvidia driver
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive TERM=linux apt-get install -q -y \
        wget \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* \
    && wget -q --show-progress --progress=bar:force:noscroll http://us.download.nvidia.com/XFree86/Linux-x86_64/$NVIDIA_DRIVER_VERSION/NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION.run -O /tmp/NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION.run \
        && cd /tmp \
        && sh NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION.run --extract-only \
        && cp /tmp/NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION/libnvidia-cbl.so.$NVIDIA_DRIVER_VERSION /usr/lib/x86_64-linux-gnu/ \
        && cp /tmp/NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION/libnvidia-glvkspirv.so.$NVIDIA_DRIVER_VERSION /usr/lib/x86_64-linux-gnu/ \
        && cp /tmp/NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION/libnvidia-rtcore.so.$NVIDIA_DRIVER_VERSION /usr/lib/x86_64-linux-gnu/ \
        && rm -rf /tmp/NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION /tmp/NVIDIA-Linux-x86_64-$NVIDIA_DRIVER_VERSION.run

# [Option] Install zsh
# ARG INSTALL_ZSH="true"
# [Option] Upgrade OS packages to their latest versions
ARG UPGRADE_PACKAGES="true"
# [Option] Enable non-root Docker access in container
ARG ENABLE_NONROOT_DOCKER="true"
# [Option] Use the OSS Moby CLI instead of the licensed Docker CLI
# ARG USE_MOBY="true"

# Install needed packages and setup non-root user. Use a separate RUN statement to add your
# own dependencies. A user of "automatic" attempts to reuse an user ID if one already exists.
ARG USERNAME=automatic
ARG USER_UID=1000
ARG USER_GID=$USER_UID
COPY .devcontainer/library-scripts/*.sh /tmp/library-scripts/
RUN apt-get update \
    && /bin/bash /tmp/library-scripts/common-debian.sh "${INSTALL_ZSH}" "${USERNAME}" "${USER_UID}" "${USER_GID}" "${UPGRADE_PACKAGES}" "true" "true" \
    # Use Docker script from script library to set things up
    && /bin/bash /tmp/library-scripts/docker-debian.sh "${ENABLE_NONROOT_DOCKER}" "/var/run/docker-host.sock" "/var/run/docker.sock" "${USERNAME}" "${USE_MOBY}" \
    # Clean up
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* /tmp/library-scripts/

# Setting the ENTRYPOINT to docker-init.sh will configure non-root access to 
# the Docker socket if "overrideCommand": false is set in devcontainer.json. 
# The script will also execute CMD if you need to alter startup behaviors.
ENTRYPOINT [ "/usr/local/share/docker-init.sh" ]
CMD [ "sleep", "infinity" ]

# Install Bazelisk.
# Bazelisk installs Bazel based on local .bazelversion or environment
# variables, so this build container isn't strictly immutable.
ARG BAZELISK_VERSION=1.6.1
RUN curl https://github.com/bazelbuild/bazelisk/releases/download/v${BAZELISK_VERSION}/bazelisk-linux-amd64 \
    -Lo /usr/local/bin/bazel && \
    chmod 755 /usr/local/bin/bazel

# Install system package dependencies.
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive TERM=linux apt-get install -q -y \
        git \
        git-lfs \
        python \
        python3-dev \
        openjdk-11-jre-headless \
    && apt-get autoremove -y && apt-get clean && rm -rf /var/lib/apt/lists/*

# install required graphics libraries
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive TERM=linux apt-get install -q -y \
        libxcursor-dev \
        libxrandr-dev \
        libxinerama-dev \
        libxi-dev \
    && apt-get autoremove -y && apt-get clean && rm -rf /var/lib/apt/lists/*
