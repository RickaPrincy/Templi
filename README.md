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

## Writing a template :rocket:

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
## Using the Templi Cli :first_quarter_moon: 
#### :warning: Read this [file](./templi.json.md) to understand how templi.json works

### 1. Generate templi.json with with (or create it from 0) : `templi configure`

- Place your template in a folder and run  (this generate templi.json base to your template)
```bash
templi configure -t <path_to_the_template>` 
# -t or --template
#if path is not given from option, it will be prompted 
```

Example: 

![configure template](images/configure.png)

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

### 2. Generating templates with: `templi generate` 

- Just run
```bash
templi generate -t <path_to_the_template> -o <path_to_the_output>
# -t or --template
# -o or --output
# if one the option is not given, the it will be prompted 
```  

![configure template](images/generate.png)

# Using Templi library :palm_tree:

```c++
//Signature
nampespace Templi{
    //Simple configure
    void configure(string template_path, vectorstring ignored_path={});

    //Ask the path if the given template_path is empty
    void configure_process(String template_path);

    //Generate without templi.json
    void generate(String template_path,String output_path, MapString values, VectorString ignored_path = {});

    //Generate with templi.json
    void Templi::generate_process(Templi::String template_path, Templi::String output_path);
}

//Example for Templi::generate
Templi::generate("template", "output_path", {
    {"name", "Templi"},
    {"version", "1.0.0"},
    {"date", "2023-01-01"},
    {"Me", "RickaPrincy"},
    {"functionName", "sayHelloWorld"}
});
```
# License

This project is licensed under the [MIT License](License.txt).