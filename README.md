# watermarker
This was developed for use on Windows 10, but can be used on any Linux distribution.

Depenencies:
- Qt5
- CMake
- GCC

#### Download and install Qt5:
1. Visit the Qt [download page](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) for open source installs.
2. Scroll to the bottom of the page and press the button **Download the Qt Online Installer**.
3. The website will auto-identify the current OS and provide a download for the installer.
4. Download and run the installer.
5. On the `Qt Setup` page, expand the line with **Qt 5.15.0** and select **MinGW 8.1.0 64 bit**. The only other thing to be selected on this page is **Qt Creator** under **Tools** which is not optional.

#### Download and install the latest version of CMake:
1. Visit the CMake [download page](https://cmake.org/download/).
2. For Windows, download the binary distribution `Windows win64-x64 Installer`.
3. For Linux, donwload the binary distribution `Linux x86_64` or just use the package manager like a normal person.
4. Run the installer.

#### Install GCC:
1. For Windows, open an elevated-PowerShell and run ```choco install mingw --version 8.1.0```.
2. Ensure that it is installed correctly by running ```gcc``` and observing a fatal error.

https://stackoverflow.com/questions/49982419/how-to-release-a-qt-c-application-on-linux-and-windows
