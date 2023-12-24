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
## Using the Templi Cli :bookmark: 
#### :warning: YOU CAN SCROLL DOWN A LITTLE TO READ HOW `TEMPLI.JSON` WORKS.

### 1. Configure templates with : `templi configure` (or create templi.json from 0)

- Place your template in a folder and run  (this generate templi.json base to your template)
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

## Using the Templi Library :bookmark: 

### OptionA: Generate template with: `Templi::generate()`

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

### OptionB: Generate using: `templi.json`
The best part of `templi` is that you can simply create a file named `templi.json` at the root of your template, and `templi` will interactively prompt you to provide values for the keys specified in the `templi.json`.
#### a. `templi.json` Structure

Attributes of `templi.json`:

- **keys**:
  - **description**: An array containing a list of dynamic words in your template.
  - **type**: array
  - **items**:
    - **key**:
      - **description**: A string representing the key name in your template; it cannot be empty (e.g., hello {{you}} -> the key is `you`).
      - **type**: string
    - **type**:
      - **description**: Determines how the key value will be prompted to the user.
      - **type**: "input" | "bool" | array of string (array containing string)
        - **input**: Will be a normal input.
        - **bool**: Will ask for `y` (yes) or `n` (no) and get `true` or `false` as the value.
        - **array of string**: Will ask which value inside the array the user wants.
    - **label**:
      - **description**: Text that will be printed on the prompt input.
      - **type**: string
    - **default** (optional):
      - **description**: Default value if the user leaves the input empty.
      - **type**: `string` if `type != bool` and `boolean` if `type == bool`
    - **required** (optional):
      - **description**: Boolean specifying if the user cannot leave the prompt empty (if default is given, then this will do nothing).
      - **type**: boolean
    - **clean** (optional):
      - **description**: Will delete all spaces in the user input (useful if you want something clean without spaces).
- **ignored_paths** (optional):
  - **description**: An array containing file paths to exclude during parsing (useful if you have a huge template, so you can exclude some paths that are unnecessary to parse).
  - **type**: Array of string

#### b. Create templi.json from 0

You can extract keywords from your template and manually create `templi.json`. Here is an example of `templi.json`:

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
If you are a little bit lazy to retrieve all the keywords in your template, you can simply use `Templi::configure` to do it. 

`Templi::configure` will extract all keywords in your template, write them to a `templi.json`, and include all files that don't contain a keyword in `ignored_paths` to your template.

`Templi::configure_process` performs the same task as `Templi::configure`. However, in `configure_process`, if the path is empty, it will be prompted for input (useful if you're creating your own CLI project starter).


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

To generate your project from a Templi template using `templi.json`, you should use `Templi::generate_process` instead of `Templi::generate`.

```c++
//Signature
namespace Templi {
    void Templi::generate_process(Templi::String template_path, Templi::String output_path);
}

//Example
Templi::generate("template", "ouptut");
```
# License

This project is licensed under the [MIT License](License.txt).