# Templi :memo: 

![templi](images/version.png)

Templi is a groundbreaking tool designed to expedite the template file generation process. It operates as both a powerful library and an associated program (CLI) for straightforward usage.

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

# Getting started

## How it works ???

### 1. Writing a template :rocket:

- First, create a folder for your template

- Start to create some file and insert the names of the words you wish to replace within the `{{}}` placeholders.

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
### 2. OptionA: Generate template with: `Templi::generate()`

```c++
//Signature
nampespace Templi{
    void generate(String template_path,String output_path, MapString values, VectorString ignored_path = {});
}

//Example
Templi::generate("template", "output_path", {
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

#### Param4(Optional):
- **type**: using VectorString = **std::vector\<std::string\>**
- **Description**: A vector containing all paths not to be configured. 

### 2. OptionB: Generate using: `templi.json`

The best part of `templi` is that you can just use create a file `templi.json` on root of your template and templi will be interactive to ask the value all some keys specify in the `templi.json`

#### a. templi.json structure
`templi.json` attribute:
- **keys**: 
    - **description**: Array containing list of dinamics words in your template
    - **type**: array
    - **items**:
        - **key**: 
            - **description**: String which is the key name on your template and cannot be empty (ex: hello {{you}} -> the key is `you`)
            - **type**: string 
        - **type**: 
            - **description**: Determine how the key value will be prompt to the user
            - **type**: "input" | "bool" | array of string (array containing string)
                - **input**: Will be normal input
                - **bool**: Will ask for `y`(yes) or `n`(no) and get `true` or `false` as value
                - **array of string**: Will ask which value inside the array the user want
        - **label**: 
            - **desciption**: Text will be printed on the prompt input
            - **type**: string
        - **default** (optional):
            - **description**: default value if the user leave the input empty
            - **type**: `string` if `type != bool` and `boolean` if `type == bool`
        - **required** (optional):
            - **description**:  Boolean specify if the user cannot leave the prompt empty (if default is given, then this will do anything)
            - **type**: boolean 
        - **clean** (optional):
            - **description**: Will delete all space of the user input (utils if you want something clean without space)
- **ignored_paths** (optional):
    - **description**: Array containing files paths to exclude during parsing (utils if you have a huge template, so you can exclude some paths which is unecassry to parse)
    - **type:**: Array of string

#### b. Create templi.json from 0 :blue_book:

You can retrieve key words in your template and create the templi.json manually. This is an example of `templi.json`

```json
{
    "ignored_paths": [
        "templi.json",
        "ignored_file.txt"
    ],
    "keys": [
        {
            "key": "author_name",
            "label": "Who is the author",
            "type": "input",
            "default": "RickaPrincy",
            "required": true,
            "clean": true
        },
        {
            "key": "project_name",
            "label": "What is your project",
            "type": ["templi", "ctemplate"]
        },
        {
            "key": "is_ok",
            "label": "Are you ok ?",
            "type": "bool",
            "default": false
        }
    ]
}
```


####  c. Create templi.json base using: `Templi::configure()` or `Templi::configure_process()`
If you are a lit bit lazy to retrieve all the key words in your template, then you can just use `Templi::configure` to do it.
`Templi::configure` will retrieve all key words in your template then write them in a `templi.json` and will add all file which doesn't contain a key word in your template.

`Templi::configure_process` does the same thing as `templi:configure` but in configure_process, if the path is empty, it will be asked as a prompt (utils if you're creating your own CLI project starter)

```cpp
//Signature
namespace templi{
    void configure(string template_path, vectorstring ignored_path={});
    void configure_process(String template_path);
}

//Example:
Templi::configure("template") /*as the ignored_path is {} by default*/;

```
#### Param1:
- **type**: using String = **std::string**
- **Description**: string representing the path to the folder containing the template to be configured.

#### Param2(Optional):
- **type**: using VectorString = **std::vector\<std::string\>**
- **Description**: A vector containing all paths not to be configured. 

Example fo output:
```json
{
    "ignored_paths": [
        "templi.json"
    ],
    "keys": [
        {
        "key": "author_name",
        "label": "",
        "type": "input"
        },
        {
        "key": "ignored",
        "label": "",
        "type": "input"
        },
        {
        "key": "is_ok",
        "label": "",
        "type": "input"
        }
    ] 
}
```

#### d. Generate template using templi.json with: `Templi::generate_process()`

To generate your project from a templi template using `templi.json` you have to use `Templi::generate_process` instead of `Templi::generate`

```c++
//Signature
namespace Templi {
    void Templi::generate_process(Templi::String template_path, Templi::String output_path);
}

//Example
Templi::generate("template", "ouptut");
```
## Using the Templi Cli :bookmark: 

- To use the Templi CLI, you need to install it on your machine or have the binary. 

### 1. Configure templates with : `templi configure`

- Place your template in a folder and run 
```bash
templi configure -t <path_to_the_template>` 
# -t or --template
#if path is not given from option, it will be prompted 
```

Example: 

![configure template](images/configure.png)

### 2. Generating templates with: `templi generate` 

- Just run
```bash
templi generate -t <path_to_the_template> -o <path_to_the_output>
# -t or --template
# -o or --output
# if one the option is not given, the it will be prompted 
```  

![configure template](images/generate.png)

# License

This project is licensed under the [MIT License](License.txt).