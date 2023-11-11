# Build and install Templi :hammer:

## Dependencies :paperclip:

Before building and using Templi, ensure that the following dependencies are met:

- CMake (Version 3.27 or later)
- C++ Compiler with C++17 support

## Building Templi :hammer:

To build Templi, follow these steps:

1. Clone the Templi repository:

    ```bash
    git clone https://github.com/RickaPrincy/Templi.git
    cd templi
    git submodule update --init --recursive
    ```

2. Navigate to the Templi directory:

    ```bash
    cd templi
    ```

3. Create a build directory:

    ```bash
    mkdir build
    cd build
    ```

4. Run CMake to configure the build:
    - Basic :
        ```bash
        cmake -S .. -B .
        ```

    - Options

        ```cmake
        option(TEMPLI_CLI_BUILD "Build Templi cli" ON)
        option(TEMPLI_CLI_INSTALL "Install Templi cli" ON)
        option(TEMPLI_LIB "Build Templi lib" ON)
        option(TEMPLI_LIB_INSTALL "Install Templi lib" ON)
        option(TEMPLI_TEST "Build templi test" OFF)
        ```

        ```bash
        cmake -Doption1=Value -Doption2=Value -S .. -B
        
        #example1: 
        cmake -DTEMPLI_CLI_BUILD=OFF -S .. -B
        
        #example2: 
        cmake -DTEMPLI_TEST=ON -DTEMPLI_LIB_INSTALL=OFF -S .. -B
        ```
5. Build Templi:
    - Build only 

        ```bash
        make
        ```
    - Build and install ( as administrator )

        ```bash
        make install
        ```
## Usage

Once built, you can use Templi by running the following commands:

- To configure templates:

    ```bash
    ./templi --configure
    ```

- To generate templates:

    ```bash
    ./templi --generate
    ```

Templi will prompt you for necessary values during the configuration and generation processes.