# 🛠️ `templi.json` — Template Engine Configuration

`templi.json` acts as the blueprint for your template repository. It dictates how **Templi** interacts with the user, validates input, manages file exclusions, and executes shell scripts during generation.

---

## 📋 Configuration Overview

```json
{
  "scripts": {
    "before": [
      "cp /home/user/file.txt ${{TEMPLI_OUTPUT_FOLDER}}/file.txt"
    ],
    "after": [
      "cd ${{TEMPLI_OUTPUT_FOLDER}}",
      "git init"
    ]
  },
  "copy_excludes": [
    "templi.json",
    "ignored_file.txt"
  ],
  "parse_excludes": [
    "binary.bin",
    "assets/images/**",
    "*.png"
  ],
  "placeholders": [
    {
      "type": "TEXT",
      "name": "author_name",
      "label": "Who is the author",
      "validators": [
        {
          "pattern": "required"
        },
        {
          "pattern": "[a-z]",
          "message": "Must be lowercase"
        }
      ]
    },
    {
      "name": "project_name",
      "label": "What is your project",
      "type": "SELECT",
      "choices": [
        "templi",
        "another"
      ]
    },
    {
      "name": "is_ok",
      "label": "Are you ok ?",
      "type": "BOOLEAN"
    }
  ]
}
```

---

## ⚙️ Attribute Reference

### 1. `placeholders`
> **Type**: `array<object>`  
> **Required**: Yes

Defines the dynamic variables found inside your template files (e.g. `{{author_name}}`) and configures how Templi prompts the user for their values.

#### 🔹 Placeholder Object Schema
| Field | Type | Required | Description |
| :--- | :--- | :---: | :--- |
| `name` | `string` | **Yes** | Identifier used inside template files (e.g., `{{author_name}}`). Cannot be empty. |
| `type` | `string` | **Yes** | Prompt mode. Allowed values: `"TEXT"`, `"BOOLEAN"`, `"SELECT"`. |
| `label` | `string` | **Yes** | The prompt phrase displayed to the user in the CLI. |
| `choices` | `array<string>` | *Conditional* | List of options. **Required** when `type` is set to `"SELECT"`. |
| `validators` | `array<object>` | Optional | Rules to validate user input before proceeding. |

#### 💡 Supported Types

- 📝 **`TEXT`**: Standard interactive text prompt.
- 🔘 **`BOOLEAN`**: Asks for a `yes/no` response (`y/n`), evaluated internally as `true` or `false`.
- 📋 **`SELECT`**: Displays an interactive menu allowing choice selection from `choices`.

#### 🧪 Validator Schema

```json
{
  "pattern": "regex_or_keyword",
  "message": "Custom error message when validation fails"
}
```
* **Common Keywords**: `"required"`
* **Regex Example**: `"^[a-z]+$"`

---

### 2. `copy_excludes`
> **Type**: `array<string>`  
> **Required**: No  
> **Default**: `[]`

An array of file paths or glob patterns to **completely ignore**. Files matching these patterns will **not** be copied to the output folder.

```json
{
  "copy_excludes": [
    "templi.json",
    "ignored_file.txt",
    "docs/drafts/**"
  ]
}
```

---

### 3. `parse_excludes`
> **Type**: `array<string>`  
> **Required**: No  
> **Default**: `[]`

An array of file paths or glob patterns to **copy directly without parsing**. Templi will transfer these files as raw byte data without processing placeholders (e.g. `{{var}}`).

> 💡 **Best Use Case**: Binary files, media assets (`.png`, `.jpg`), archives (`.zip`), or files containing template-like syntax (e.g., Vue.js / Jinja templates).

```json
{
  "parse_excludes": [
    "binary.bin",
    "assets/images/**",
    "*.png"
  ]
}
```

---

### 4. `scripts`
> **Type**: `object`  
> **Required**: No

Defines lifecycle shell hooks executed during template generation.

| Hook | Type | Description |
| :--- | :--- | :---        |
| `before` | `array<string>`| Shell commands executed **before** Templi processes and copies template files. |
| `after` | `array<string>` | Shell commands executed **after** all files have been parsed and generated. |

#### 🔑 Environment Variables
Templi exposes the target output directory via the `${TEMPLI_OUTPUT_FOLDER}` variable inside script hooks:

```json
{
  "scripts": {
    "before": [
      "echo 'Starting template generation...'"
    ],
    "after": [
      "cd ${{TEMPLI_OUTPUT_FOLDER}}",
      "git init",
      "npm install"
    ]
  }
}
```

---
## 🎯 Summary Rules

```
                      ┌──────────────────────┐
                      │    Template Files    │
                      └──────────┬───────────┘
                                 │
           ┌─────────────────────┼─────────────────────┐
           ▼                     ▼                     ▼
 ┌───────────────────┐ ┌───────────────────┐ ┌───────────────────┐
 │   copy_excludes   │ │  parse_excludes   │ │    Parsed Files   │
 ├───────────────────┤ ├───────────────────┤ ├───────────────────┤
 │ ❌ Skipped entirely│ │ 📋 Copied directly│ │ ⚙️ Evaluated &   │
 │   (Not copied)    │ │    (No parsing)   │ │    placeholders   │
 └───────────────────┘ └───────────────────┘ │    replaced       │
                                             └───────────────────┘
```
