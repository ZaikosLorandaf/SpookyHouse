# Team 7 Escape Room Repo

<!--toc:start-->
- [Team 7 Escape Room Repo](#team-7-escape-room-repo)
  - [Build on Linux](#build-on-linux)
  - [Build on Windows](#build-on-windows)
  - [Troubleshooting](#troubleshooting)
<!--toc:end-->

Let's be the best once again!!

## Build on Linux

Run the following script *inside the project directory* to build the project and
generate clangd LSP config

```sh
./build.sh
```

The resulting executable can be run using the following script

```sh
./execute.sh
```

## Build on Windows

Open as CMake project in VisualStudio

Do whatever VisualStudio does

## Troubleshooting

- Project crashes due to a failed assertion in some part of the code I don't know!
- Make sure you run the executable from the main directory, otherwise the asset
  load will fail
