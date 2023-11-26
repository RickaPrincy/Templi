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

- You can run the following command to build and install templi with cmake, but if you want other options of building templi, read [this](BUILD_INSTALL.md).

```bash
bash <(curl -s https://raw.githubusercontent.com/RickaPrincy/Templi/main/install.sh)
```

- You can also simply use Templi as a submodule.

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
    void configure(String templateFolder, String configuredPath, VectorString ignoredPaths = {});
}

//Example:
Templi::configure("__template__", "__configured__", {
    "__template__/main.js",
    "__template__/all_ignored"
});

```

#### Param1:
- **type**: using String = **std::string**
- **Description**: string representing the path to the folder containing the template to be configured.

#### Param2: 
- **type**: using String = **std::string**
- **Description**: Destination path to copy the template after configuration.

#### Param3(Optional):
- **type**: using VectorString = **std::vector\<std::string\>**

- **Description**: A vector containing all paths not to be configured. 

### 2. Generate templates: `Templi::generate()`

```c++
//Signature
nampespace Templi{
    void generate(String configuredPath,String outputFolder, MapString values);
}

//Example
Templi::generate("__configured__", "__generated__", {
    {"name", "Templi"},
    {"version", "1.0.0"},
    {"date", "2023-01-01"},
    {"Me", "RickaPrincy"},
    {"functionName", "sayHelloWorld"}
});
```

#### Param1
- **type**: using String = **std::string**
- **description**: Path to the configured template

#### Param1
- **type**: using String = **std::string**
- **description**: Path to copy the generated template

#### Param3
- **type**: using VectorString = **std::map\<std::string, std::string\>**
- **description**: The map contains values for the words found in all templates during the configuration process. The map key is the word's name. 

## Using the Templi Cli :bookmark: 

- To use the Templi CLI, you need to install it on your machine or have the binary. 

### 1. Configure templates : `templi --configure` or `templi -c`

- Place your template in a folder and run `templi --configure` or `templi -c`, then respond to all prompts, as shown in the following image: 

![configure template](images/configure.png)

### 2. Generating templates: `templi --generate` or `templi -c`

- Just run `templi --generate` or `templi -g` to generate templates. It will prompt you for all the values and outputs paths specified in the library. 

![configure template](images/generate.png)

# License

This project is licensed under the [MIT License](License.txt).