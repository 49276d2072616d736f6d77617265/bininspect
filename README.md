# bininspect

一個使用 **純 C 語言** 撰寫的跨平台檔案檢測工具。  
不依賴任何作業系統或架構專用標頭（例如 `windows.h`、`elf.h`）。  
所有分析皆透過位元組層級讀取與解析完成。

---

## 功能特色
- 取得檔案大小
- 顯示前 16 位元組（Magic bytes）
- 基本檔案類型識別（ELF、PE、PDF、ZIP、PNG、JPEG 等）
- SHA-256 雜湊計算（自行實作，無外部函式庫）
- Shannon 熵值計算（可用於判斷壓縮或封裝檔案）
- **JSON 輸出模式**（`--json`，可用於自動化工具鏈）

---

## 編譯方式
```bash
make
````

## 使用方式

```bash
./build/bininspect <file>   # 基本檔案檢測
./build/bininspect <file> --json  # JSON 輸出模式
```

---

## 授權

本專案採用 **MIT License**。
可自由使用、修改、散佈與商業用途，無額外限制。

---

# bininspect

A cross-platform file inspection tool written in **pure C**.
It does not rely on any operating-system or architecture-specific headers
(e.g. `windows.h`, `elf.h`).
All parsing is performed manually at the byte level.

---

## Features

* File size inspection
* First 16 bytes display (magic bytes)
* Basic file type detection (ELF, PE, PDF, ZIP, PNG, JPEG, etc.)
* SHA-256 hashing (custom implementation, no external libraries)
* Shannon entropy calculation (useful for detecting compression or packing)
* **JSON output mode** (`--json`, for automation and tooling integration)

---

## Build

```bash
make
```

## Usage

```bash
./build/bininspect <file>   # Basic file inspection
./build/bininspect <file> --json  # JSON output mode
```

---

## License

This project is released under the **MIT License**.
You are free to use, modify, distribute and fork it without restrictions.
