# ELEC3885 Breadboard Prototype
![build status](https://github.com/frankplow/ELEC3885_Breadboard_Prototype/actions/workflows/build.yml/badge.svg)

This is the source code for the breadboard prototype of the ELEC3885 group 4 project: A Robust and Lightweight Helmet-Mounted Safety Camera for Cyclists. This version of the software is a relatively early prototype. It targets the [32F746GDISCOVERY development board](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html), with a [B-CAMS-OMV](https://www.st.com/en/evaluation-tools/b-cams-omv.html) camera adapter sporting one of a variety of OmniVision OVxxxx camera modules. The device captures uncompressed video using the camera and stores it in a [QuickTime movie file (.mov)](https://developer.apple.com/library/archive/documentation/QuickTime/QTFF/QTFFPreface/qtffPreface.html) using an ExFAT-formatted SD card.

## Building
This is an STM32CubeIDE project. For instructions on how to build it, see the [STM32CubeIDE documentation](https://www.st.com/resource/en/user_manual/um2609-stm32cubeide-user-guide-stmicroelectronics.pdf).
