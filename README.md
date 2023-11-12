# Templi :memo: 

![templi](images/version.png)

Templi is a groundbreaking tool designed to expedite the template file generation process. It operates as both a powerful library and an associated program for straightforward usage.

# Why is Templi fast? How does it work ? :bulb:

Its unparalleled speed is attributed to a unique approach—preemptive identification of {{}} tags within template files. This process occurs in advance through template configuration and position memorization in configuration files. During template generation (word replacement), Templi simply references these configurations, seamlessly inserting the values that replace the {{}} tags.

# Installation :seedling:

For the moment, you have to build templi to use it

- Dependancies

    - CMake (Version 3.27 or later)
    - C++ Compiler with C++17 support

- You can run the following command to build templi, but if you want other options of building templi, read [this](BUILD_INSTALL.md).

```bash
bash <(curl -s https://raw.githubusercontent.com/RickaPrincy/Templi/main/install.sh)
```

- You can also simply clone and use Templi as a submodule.

# Getting started :rocket:

## Writing a template

- Insert the names of the words you wish to replace within the `{{}}` placeholders.

```bash
#ex: hello.sh 
echo "hello {{name}}"
```

```json
//package.json
{
    "Project": {{project}},
    "Author": {{author}},
    "Version": {{version}},
    "description": {{version}}
}
```
## Using the library :blue_book:

- To use the Templi library, you just need to include it in your project. I recommend using `cmake` for library integration. 

### 1. Configure templates : `Templi::configure()`

```cpp
//Signature
namespace Templi{
    std::set<std::string> configure(std::vector<std::string> paths, std::string configPath);
}

//Example:
std::set<std::string> wordsFounded;
wordsFounded = Templi::configure({"main.js", "hello.txt", "function.cpp"}, "config.templi");
```

#### Param1:
- **type**: std::vector\<std::string\>
- **Description**: A vector that contains all the paths to your templates for configuration. 

#### Param2: 
- **type**: std::string
- **Description**: The name of your config file to generate

#### Return
- **type**: std::set\<std::string\>
- **Description**: A set containing all unique words found in all configured template files. 

### 2. Generate templates: `Templi::generate()`

```c++
//Signature
nampespace Templi{
    void generate(std::string configPath, std::map<std::string, std::string> values, std::map<std::string, std::string> outputs);
}

//Example
std::map<std::string, std::string> 
    outptusFiles = {
        {"main.js", "main.output"},
        {"echo.sh", "echo.output.sh"}
    }, 
    values = { 
        {"name", "User name"},
        {"version", "LOL"}
    };

Templi::generate("config.templi", values, outptusFiles);
```

#### Param1
- **type**: std::string 
- **description**: The name of the config file of the template

#### Param2
- **type**: std::map\<std::string, std::string\>
- **description**: The map contains values for the words found in all templates during the configuration process. The map key is the word's name. 

#### Param3
- **type**: std::map\<std::string, std::string\>
- **description**: The map contains output file paths for all configured template files. The key is the configured template file path.

## Using the Templi Cli :bookmark: 

- To use the Templi CLI, you need to install it on your machine or have the binary. 

### 1. Configure templates : `templi --configure` or `templi -c`

- Place your template files in a folder and run `templi --configure` or `templi -c`, then respond to all prompts, as shown in the following image: 

![configure template](images/configure.png)

### 2. Generating templates: `templi --generate` or `templi -c`

- Just run `templi --generate` or `templi -g` to generate templates. It will prompt you for all the values and outputs paths specified in the library. 

![configure template](images/generate.png)

# License

This project is licensed under the [MIT License](License.txt).