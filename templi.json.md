# templi.json

`templi.json` is like a file configuration for your template. Templi uses it to determine how your name's value will be prompted.

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
    "excludes": [
        "templi.json",
        "ignored_file.txt"
    ],
    "placeholders": [
        {
            "name": "author_name",
            "label": "Who is the author",
            "type": "INPUT",
            "default": "RickaPrincy",
            "required": true,
            "remove_spaces": true
        },
        {
            "name": "project_name",
            "label": "What is your project",
            "type": "SELECT"
            "choices": ["templi", "ctemplate"]
        },
        {
            "name": "is_ok",
            "label": "Are you ok ?",
            "type": "BOOLEAN",
            "default": "false"
        }
    ]
}
```

Attributes of `templi.json`:

- **`placeholders`**:
    - **description**: An array containing definitions for the dynamic words (placeholders) found within your template files.
    - **type**: `array`
    - **items**:
        - **`name`**:
            - **description**: A string representing the placeholder name used in your template files (e.g., in `hello {{you}}`, the name is `you`). This field is mandatory and cannot be empty.
            - **type**: `string`
        - **`type`**:
            - **description**: Determines the method Templi will use to prompt the user for the value of this key.
            - **type**: `"input"` | `"boolean"` | `"select"`
                - **`INPUT`**: Presents a standard text input prompt to the user.
                - **`BOOLEAN`**: Asks the user for a yes/no response (`y` or `n`), which will be interpreted as `true` or `false`.
                - **`SELECT`**: Presents a list of `choices` to the user, allowing them to select one value. The `choices` should be defined in the `choices` attribute of the key.
        - **`label`**:
            - **description**: The text displayed to the user as the prompt for this key's value.
            - **type**: `string`
        - **`default`** (optional):
            - **description**: The value that will be used if the user leaves the input empty.
            - **type**: `string` (if `type` is `"input"` or `"select"`) or `boolean` (if `type` is `"boolean"`)
        - **`required`** (optional):
            - **description**: A boolean value indicating whether the user must provide a value for this key. If set to `true`, the user cannot leave the prompt empty (note: this has no effect if a `default` value is provided).
            - **type**: `boolean`
        - **`remove_spaces`** (optional):
            - **description**: A boolean value. If set to `true`, all whitespace characters will be removed from the user's input for this key. This is useful for ensuring clean values without spaces.
            - **type**: `boolean`
- **`excludes`** (optional):
    - **description**: An array of strings, where each string is a file path or pattern to exclude from Templi's processing. This is beneficial for optimizing performance by skipping large or irrelevant files within your template directory.
    - **type**: `array` of `string`
- **`scripts`** (optional):
    - **description**: An object containing scripts to be executed at specific stages of the template generation process.
    - **type**: `object`
        - **`before`** (optional):
            - **description**: An array of shell commands to execute *before* Templi starts generating files. You can use the environment variable `${TEMPLI_OUTPUT_FOLDER}` to refer to the output directory.
            - **type**: `array` of `string`
        - **`after`** (optional):
            - **description**: An array of shell commands to execute *after* Templi has finished generating all the files. You can use the environment variable `${TEMPLI_OUTPUT_FOLDER}` to refer to the output directory.
            - **type**: `array` of `string`
