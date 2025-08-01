[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://github.com/darbyjohnston/DJV/actions/workflows/ci-workflow.yml/badge.svg)](https://github.com/darbyjohnston/DJV/actions/workflows/ci-workflow.yml)

# ![DJV Icon](etc/Icons/DJV_Icon_32.svg) DJV

DJV is an open source application for playback and review of image
sequences. DJV can playback high resolution image sequences in real
time, with audio, A/B comparison, and color management.

Features include:
* Support for high resolution and high bit depth images
* A/B comparison with wipe, overlay, and difference modes
* Timeline support with OpenTimelineIO
* Color management with OpenColorIO
* Multi-track audio with variable speed and reverse playback
* Experimental support for USD files
* Available for Linux, macOS, and Windows

[Documentation](https://darbyjohnston.github.io/DJV/index.html)

DJV is built with the [tlRender](https://github.com/darbyjohnston/tlRender) library.

Example of two images being compared with a wipe:

![Screenshot](etc/Images/djv_screenshot1.png)

Example of two images being compared with a horizontal layout:

![Screenshot](etc/Images/djv_screenshot2.png)


## Downloads

**NOTE**: Download packages only include a minimal set of video codecs. To
enable full support for video codecs, either compile from source or replace
the FFmpeg shared library files.


## Building on Linux

Dependencies:
* CMake 3.31

Install system packages (Debian based systems):
```
sudo apt-get install xorg-dev libglu1-mesa-dev mesa-common-dev mesa-utils libasound2-dev libpulse-dev
```

Install system packages (Rocky 9):
```
sudo dnf install libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel mesa-libGL-devel
```

Clone the repository:
```
git clone https://github.com/darbyjohnston/DJV.git
```
Run CMake with the super build script:
```
cmake -S DJV/etc/SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=$PWD/Release/install -DCMAKE_PREFIX_PATH=$PWD/Release/install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Run the application:
```
./Release/DJV/src/DJV-build/bin/djv/djv
```


## Building on macOS

Dependencies:
* Xcode
* CMake 3.31

Clone the repository:
```
git clone https://github.com/darbyjohnston/DJV.git
```
Run CMake with the super build script:
```
cmake -S DJV/etc/SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=$PWD/Release/install -DCMAKE_PREFIX_PATH=$PWD/Release/install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Run the application:
```
./Release/DJV/src/DJV-build/bin/djv/djv
```

The CMake variable `CMAKE_OSX_ARCHITECTURES` can be used to specify the build
architecture:
```
-DCMAKE_OSX_ARCHITECTURES=x86_64
```
```
-DCMAKE_OSX_ARCHITECTURES=arm64
```

These aliases are convenient for switching between architectures:
```
alias arm="env /usr/bin/arch -arm64 /bin/zsh --login"
alias intel="env /usr/bin/arch -x86_64 /bin/zsh --login"
```


## Building on Windows

Dependencies:
* Visual Studio 2022
* CMake 3.31
* MSYS2 (https://www.msys2.org) for compiling FFmpeg.
* Strawberry Perl (https://strawberryperl.com/) for compiling network support.
* Python 3.11 for compiling USD.
* NSIS (https://nsis.sourceforge.io/Main_Page) for packaging.

Open the Visual Studio command console "x64 Native Tools Command Prompt for VS 2022".
This can be found in the Start menu, in the "Visual Studio 2022" folder.

Clone the repository:
```
git clone https://github.com/darbyjohnston/DJV.git
```
Run CMake with the super build script:
```
cmake -S DJV\etc\SuperBuild -B Release -DCMAKE_INSTALL_PREFIX=%CD%\Release\install -DCMAKE_PREFIX_PATH=%CD%\Release\install -DCMAKE_BUILD_TYPE=Release
```
Start the build:
```
cmake --build Release -j 4 --config Release
```
Run the application:
```
set PATH=%CD%\Release\install\bin;%PATH%
```
```
.\Release\DJV\src\DJV-build\bin\djv\Release\djv
```

