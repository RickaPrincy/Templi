# Templi :memo: 

![templi](images/version.png)

Templi is a groundbreaking tool designed to expedite the template file generation process. It operates as both a powerful library and an associated program (CLI) for straightforward usage.

# Installation :seedling:

- Archlinux

```bash
yay -Sy templi
```
For the moment, you have to build templi to use it if you use another system (not archlinux)

- Dependancies

    - CMake (Version 3.27 or later)
    - C++ Compiler with C++17 support
    - [rcli](https://github.com/RickaPrincy/rcli)

```bash
bash <(curl -s https://raw.githubusercontent.com/RickaPrincy/Templi/main/install.sh)
```

- Build manually

```bash
git clone -b v3.2.0 https://github.com/RickaPrincy/Templi.git

cd Templi

mkdir build

cd build

cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

sudo make install

cd ../..

rm -rf Templi
```
#### :warning: If some libs are not found after building manually

Identify the installation path of the missing library. For example, let's assume the library is installed in `/usr/local/lib` (on linux it should be there).

If you are using Linux, add the following code to your `~/.zshrc` or `~/.bashrc` based on what you use (replacing `/usr/local/lib` with the actual installation path):

```bash
export LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH
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
templi generate -t <path-to-the-template> -o <path-to-the-output> -p <path-suffix>
# -t or --template
# -o or --output
# -p or --path-suffix (optional) (for monorepo templates)
# if one the option is not given, the it will be prompted 
```  
## :warning: output_path can be retrieved to your template with {{TEMPLI_OUTPUT_FOLDER}}
![configure template](images/generate.png)

# Using Templi library :palm_tree:

```c++
//Signature
nampespace Templi{
    // Simple configure
    void configure(string template_path, vectorstring ignored_path={});

    // Generate without templi.json
    void generate(String template_path,String output_path, MapString values, VectorString ignored_path = {});

    // Generate with templi.json
    void generate_with_templi_config(String template_path, String output_path, String path_suffix = "");
    
    // Useful when you want to read a template.json file or save a config
	class JSONConfig
	{
	public:
		VectorString _ignored_paths{}, _before{}, _after{};
		std::vector<Key> _keys{};

		void read_config(String template_path);
		void save_config(String template_path);

		JSONConfig(){};
		JSONConfig(String template_path);
	};	// JSONConfig
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

# More example

[templi-templates](https://github.com/RickaPrincy/templi-templates)

# License

This project is licensed under the [MIT License](License.txt).
