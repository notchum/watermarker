# watermarker
This was developed for use on Windows 10 with MinGW, but can be used on any Linux distribution.

Depenencies:
- Qt5
- OpenCV
- CMake
- GCC

## Install

### Download and install Qt5:
1. Visit the Qt [download page](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) for open source installs.
2. Scroll to the bottom of the page and press the button **Download the Qt Online Installer**.
3. The website will auto-identify the current OS and provide a download for the installer.
4. Download and run the installer.
5. On the `Qt Setup` page, expand the line with **Qt 5.15.0** and select **MinGW 8.1.0 64 bit**. The only other thing to be selected on this page is **Qt Creator** under **Tools** which is not optional.

### Download and install OpenCV:
1. Download pre-built OpenCV package from [OpenCV-MinGW-Build](https://github.com/huihut/OpenCV-MinGW-Build) and download the correct installer.
2. Add `path/to/opencv/x64/mingw/bin` to the PATH

### Download and install the latest version of CMake:
1. Visit the CMake [download page](https://cmake.org/download/).
2. For Windows, download the binary distribution `Windows win64-x64 Installer`.
3. For Linux, donwload the binary distribution `Linux x86_64` or just use the package manager like a normal person.
4. Run the installer.

### Install GCC:
1. Visit the MinGW [download page](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/8.1.0/).
2. Download the **MinGW-W64 Online Installer** and run the executable.
3. On the `Settings` page, ensure Version 8.1.0, Architecture x86_64, Threads posix, Exception seh, and Build 0.
4. Ensure that it is installed correctly by running ```gcc``` and observing a fatal error.

## Configure

### Configure for VSCode
1. Install the extension [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools).
2. Select *Debug* for build variant and *MinGW/GCC 8.1.0* for the active kit.
3. To ensure proper syntax highlighting for Qt includes, add `path/to/Qt/%VERSION%/mingw81_64/bin/**` to the `includePath`.

https://stackoverflow.com/questions/49982419/how-to-release-a-qt-c-application-on-linux-and-windows
