# radiance
a place to practice putting pixels on screen

## Developmnent Setup

Currently, this setup requires an NVIDIA GPU and only has only been tested on Ubuntu 20.04, even though ImGui is cross-platform itself.

1. Install [VS Code.](https://code.visualstudio.com/).
1. Install [Docker](https://docs.docker.com/engine/install/ubuntu/).
1. Install [NVIDIA Docker runtime](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html).
1. Install the [VS Code Remote Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers).
1. Copy the `arcius/dotfiles/.devcontainer` example directory with its contents into your workspace folder as `.devcontainer`.
1. Invoke VS Code command `Remote-Containers: Rebuild and Reopen in Container`.

The rest of the commands assume the setup was successful.