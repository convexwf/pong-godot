# Godot GDExtension C++ Examples using Docker Compilation Environment

This solution is based on the [mrt-prodz/docker-godot-gdextension-builder](https://github.com/mrt-prodz/docker-godot-gdextension-builder).

You can check more details on the [Godot-GDExtension C++ 环境搭建 (Docker+MinGW/跨平台) | Convexwf's Kirakira Blog](https://blog.convexwf.com/zh/2024/05/godot-gdextension-cpp-environment-using-docker-and-mingw.html).

## Intruction

**[Windows]**

You have to run all the following commands from a Git Bash prompt.

### Clone the repository

```bash
git clone https://github.com/convexwf/godot-gdextension-cpp-examples
cd godot-gdextension-cpp-examples
```

### Build the Docker image

```bash
# execute on windows
bash shell/build.sh windows
# or bash shell/build_windows.sh

# execute on linux
bash shell/build.sh linux
# or bash shell/build_linux.sh
```

Or you can build the Docker image manually:

```bash
docker build -t convexwf/godot-gdextension-cpp-builder .
```

Or you can pull the image from Docker Hub:

```bash
docker pull convexwf/godot-gdextension-cpp-builder
```

### Build the C++ binding library

If you have already executed the previous `bash shell/build.sh` command, you can skip this step.

The source files in the `src` directory of this repository are copies from the Godot 4.2 documentation.

**[Windows]**

```bash
docker run --rm \
    -v /${PROJECT_DIR}:/app \
    convexwf/godot-gdextension-cpp-builder \
    bash -c "cd /app/godot-cpp && source activate gde && scons platform=windows"
```

**[Linux]**

```bash
docker run --rm \
    -v $(pwd):/app \
    convexwf/godot-gdextension-cpp-builder \
    bash -c "cd /app/godot-cpp && source activate gde && scons platform=linux"
```

## Reference

- [mrt-prodz/docker-godot-gdextension-builder: Building Godot 4 GDExtension C++ example with Docker](https://github.com/mrt-prodz/docker-godot-gdextension-builder)
- [GDExtension C++ example — Godot Engine (stable) documentation in English](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html)
- [Godot-GDExtension C++ 环境搭建 (Docker+MinGW/跨平台) | Convexwf's Kirakira Blog](https://blog.convexwf.com/zh/2024/05/godot-gdextension-cpp-environment-using-docker-and-mingw.html)
