# Templi.json :first_quarter_moon_with_face:

`templi.json` is like a file configuration for your template. Templi uses it to determine how your key's value will be prompted.

Example:

```json
{
    "scripts": {
        "before":[
            "cp /home/user/file.txt ${{TEMPLI_OUTPUT_FOLDER}}/file.txt"
        ],
        "after": [
            "cd ${{TEMPLI_OUTPUT_FOLDER}}",
            "git init",
        ],
    },
    "ignored_paths": [
        "templi.json",
        "ignored_file.txt"
    ],
    "keys": [
        {
            "key": "author_name",
            "label": "Who is the author",
            "type": "INPUT",
            "default": "RickaPrincy",
            "required": true,
            "clean": true
        },
        {
            "key": "project_name",
            "label": "What is your project",
            "type": "SELECT"
            "choices": ["templi", "ctemplate"]
        },
        {
            "key": "is_ok",
            "label": "Are you ok ?",
            "type": "BOOLEAN",
            "default": "false"
        }
    ]
}
```

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
        - **INPUT**: Will be a normal input.
        - **BOOLEAN**: Will ask for `y` (yes) or `n` (no) and get `true` or `false` as the value.
        - **SELECT**: Will ask which value inside the array `choices` the user wants.
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
