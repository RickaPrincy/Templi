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
            "type": "TEXT"
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
            - **type**: `"text"` | `"boolean"` | `"select"`
                - **`TEXT`**: Presents a standard text input prompt to the user.
                - **`BOOLEAN`**: Asks the user for a yes/no response (`y` or `n`), which will be interpreted as `true` or `false`.
                - **`SELECT`**: Presents a list of `choices` to the user, allowing them to select one value. The `choices` should be defined in the `choices` attribute of the key.
        - **`label`**:
            - **description**: The text displayed to the user as the prompt for this key's value.
            - **type**: `string`
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
