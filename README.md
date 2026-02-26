# MeowPassword C

[![CI](https://github.com/SpaceTrucker2196/MeowPasswordC/actions/workflows/ci.yml/badge.svg)](https://github.com/SpaceTrucker2196/MeowPasswordC/actions/workflows/ci.yml)
[![C/C++ CI](https://github.com/SpaceTrucker2196/MeowPasswordC/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/SpaceTrucker2196/MeowPasswordC/actions/workflows/c-cpp.yml)
[![CMake on a single platform](https://github.com/SpaceTrucker2196/MeowPasswordC/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/SpaceTrucker2196/MeowPasswordC/actions/workflows/cmake-single-platform.yml)

A secure, memorable password generator that uses cat names to create strong passwords. Ported from Swift to pure C11 for Linux/Debian systems.

## Features

- Generates passwords using 16,913 embedded cat names
- Shannon entropy analysis for password strength
- Kolmogorov complexity estimation
- Pattern complexity and character diversity scoring
- Configurable password length and complexity
- Clipboard support via xclip
- No external dependencies (pure C11)

## Building

### Using Make

```bash
make
```

### Using CMake

```bash
mkdir build && cd build
cmake ..
make
```

## Installation

```bash
sudo make install
```

## Usage

```bash
# Generate a password with default settings
./meowpass

# Generate with specific length
./meowpass -l 20

# Generate with specific complexity (1-10)
./meowpass -c 8

# Verbose output with analysis
./meowpass -v

# Copy to clipboard
./meowpass --copy

# Run tests
./meowpass --test

# Show help
./meowpass --help
```

## How It Works

1. Selects random cat names from the embedded dictionary
2. Joins names in lowercase
3. Randomly capitalizes some characters
4. Inserts random digits
5. Replaces some characters with symbols
6. Analyzes resulting password for entropy and complexity

## Complexity Analysis

The password analysis includes:

- **Shannon Entropy**: Information entropy in bits per character
- **Compression Ratio**: Kolmogorov complexity approximation
- **Pattern Complexity**: Substring uniqueness score
- **Character Diversity**: Coverage of lowercase, uppercase, digits, symbols

## Requirements

- C11 compiler (gcc or clang)
- Linux system
- Optional: xclip for clipboard support

## License

MIT License - see LICENSE file for details.

## Author

Jeffrey Kunzelman

## Credits

Original Swift implementation: MeowPassword
