# Base image
FROM mcr.microsoft.com/devcontainers/base:noble

USER vscode

ENV DEBIAN_FRONTEND=noninteractive
RUN sudo apt-get update
RUN sudo apt-get install clang-format clang-tidy clazy git python3 pipx  qt6-base-dev curl -y

# install github-cli in docker for convenience
RUN type -p curl >/dev/null || (sudo apt update && sudo apt install curl -y)
RUN curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
RUN sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
RUN sudo apt update
RUN sudo apt install gh -y

RUN pipx install pre-commit cmakelang

RUN rm -rf /home/vscode/.ssh

WORKDIR /workspace

CMD ["/bin/bash"]
