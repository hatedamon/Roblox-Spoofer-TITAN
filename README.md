# TITAN Spoofer/Woofer (Roblox) 💽

**[TITAN](https://discord.gg/ch6yngrRMz)**'s spoofer is a tool designed to spoof various hardware identifiers (HWIDs) on your system 🖥️ Specifically those Roblox detect when trying to determine who you are 👤 Ban evading! :3

## Open Source Project 🔭

I'm not gonna paywall such a simple program 🤦 like some people like to do.

## What's TITAN ⁉️

**[TITAN](https://discord.gg/ch6yngrRMz)**'s a project me and some other developers are working on, an executor plus other exploiting tools to make exploiting more accessible to everybody. That starts with this Spoofer/Woofer. [Discord](https://discord.gg/ch6yngrRMz)'

## Features 💎

- **MAC Address Spoofing**: 🛜 Spoof the MAC addresses of your net adapters.
- **Volume Serial Number Spoofing**: 🚘 Change the volume serial nums of your drivers.
- **BIOS Information Spoofing**: 🔢 Modify BIOS information; baseboard serial nums.
- **HWID Spoofing**: 🪪 Change your hardware ID.
- **Snapshotting & Rollbacks**: 💫 Store and restore the original state to move back to.

## Requirements ⚠️

- Windows OS (x64 & x32) 🪟
- Admin 🎟️

## Files 📃

- `master.cpp`: Entry
- `mac.hpp` / `mac.cpp`: MAC Spoof
- `disk.hpp` / `disk.cpp`: VSN Spoof
- `bios.hpp` / `bios.cpp`: BIO & Board Spoof
- `hwid.hpp` / `hwid.cpp`: HWID Spoof
- `utils.hpp` / `utils.cpp`: Merged func

## Installation

1. Clone the repository 📂

    ```sh
    git clone https://github.com/hatedamon/Roblox-Spoofer-TITAN.git
    cd Roblox-Spoofer-TITAN
    ```

2. Ensure you have the necessary dependencies and compiler for Windows (C Compiler) 💽 For example:

    - [Microsoft Visual Studio](https://visualstudio.microsoft.com/vs/)
    - [MinGW-w64](http://mingw-w64.org/doku.php)
    - [LLVM/Clang](https://clang.llvm.org/)

## Usage 💻

1. Open the dir in your preferred IDE (Visual Studio for most of you) or compile it using your chosen compiler.

2. Run the program w/ admin privileges.

3. The program will automatically store the current system state [INCOMPLETE], spoof the identifiers [COMPLETE], and optionally restore the state if needed [INCOMPLETE].

## Author 🎓

- GitHub: [@hatedamon](https://github.com/hatedamon)
