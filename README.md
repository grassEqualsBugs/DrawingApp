# Lightweight Drawing App

A simple, extremely lightweight drawing application designed as an alternative to GIMP and Adobe Illustrator. This app focuses on ease of use, speed, and essential drawing features without unnecessary bloat.

## Features

- Layer-based system with stroke-based rendering
- Intuitive color selection with a Unity-style color wheel
- Extremely lightweight and fast

## Installation

1. Download the latest release.
2. Unzip the release.
3. Run the command 'xattr -d com.apple.quarantine DrawingApp' in the terminal to remove the quarantine attribute.
4. Run the command 'chmod +x DrawingApp' in the terminal to make the application executable.
5. Run `./DrawingApp` to start the application.

## Building at Home

1. Download the source code.
2. Run `make` in the root directory (requires GNU make to be installed)
3. Run `./DrawingApp` to start the application.
