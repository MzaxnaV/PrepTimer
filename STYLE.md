# Code Style Guide

Mechanical formatting is enforced by `.clang-format`. This document covers the
conventions that clang-format cannot check.

---

## Naming

| Category | Convention | Examples |
|---|---|---|
| Types, structs, enums | PascalCase | `Timer`, `AppMode`, `Section` |
| Enum values | PascalCase | `AppMode::Idle`, `Section::None` |
| Functions (free and member) | PascalCase | `SetWindowMode`, `RecordLap`, `FormatTime` |
| Variables and struct members | snake_case | `running`, `current_section`, `target_ms` |
| Private member variables | `m_` prefix | `m_start`, `m_accumulated_ms` |
| Global state | `g_` prefix | `g_app`, `g_pd3dDevice`, `g_hwnd` |
| Static-local persistent state | `s_` prefix | `s_name_buf`, `s_tag_buf` |

---

## Include Order

Four groups, separated by a blank line, in this order:

```cpp
#include "own_header.h"        // 1. own header (matches the .cpp filename)

#include "../app.h"            // 2. other project headers

#include "imgui.h"             // 3. third-party library headers

#include <windows.h>           // 4. system / standard library headers
#include <cstdint>
```

Never reorder within a group; alphabetical is fine but not required.

---

## Header Guards

```cpp
#ifndef FILENAME_H_
#define FILENAME_H_

// ...

#endif // FILENAME_H_
```

Use the exact filename in uppercase with `_H_` suffix. The `// FILENAME_H_`
comment on `#endif` is required.

---

## Column Alignment

clang-format aligns consecutive `=` signs in assignment blocks automatically.
Two additional cases are done by hand:

**Struct member declarations** — align names when type lengths vary significantly:

```cpp
struct Session {
    std::string              name;
    std::vector<std::string> tags;
    Section                  current_section = Section::None;
    int64_t                  unix_start      = 0;
    uint32_t                 target_ms       = 120000;
    Timer                    timer;
};
```

**Grouped free-function declarations in headers** — align return types:

```cpp
ID3D11Device*        GetDevice();
ID3D11DeviceContext* GetContext();
ID3D11RenderTargetView** GetRenderTarget();
```

Do not force alignment when there are only two entries or the types are similar
in length — only when it genuinely aids readability.

---

## Trivial One-Liner Functions

Accessor functions that do nothing but return a member may be written on a
single line. When several appear together, align the `{`:

```cpp
ID3D11Device*            GetDevice()       { return g_pd3dDevice; }
ID3D11DeviceContext*     GetContext()      { return g_pd3dDeviceContext; }
ID3D11RenderTargetView** GetRenderTarget() { return &g_mainRenderTarget; }
```

A function qualifies as a one-liner only if its body is a single `return`
statement with no logic. Anything else gets Allman braces on its own lines.

---

## Section Divider Comments

Use 71-character dividers to separate logical sections within a file:

```cpp
// -----------------------------------------------------------------------
// DX11 setup
// -----------------------------------------------------------------------
```

Use them sparingly — only when a file contains two or more clearly distinct
concerns (e.g., setup vs. per-frame work). Do not add them inside functions.

---

## File-Level Structure

`.cpp` files follow this top-to-bottom order:

1. Includes (own header → project → third-party → system)
2. File-local `static` variables
3. File-local helper functions (not declared in any header)
4. Public function implementations

Static helpers go above the first public function that uses them, not at the
bottom of the file.
