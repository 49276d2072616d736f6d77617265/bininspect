# bininspect

一個使用 **純 C 語言** 撰寫的跨平台檔案檢測工具。  
不依賴任何作業系統或架構專用標頭（例如 `windows.h`、`elf.h`）。  
所有分析皆透過位元組層級讀取與解析完成。

此工具的目標是提供一個簡潔、可攜、可擴充的基礎，用於：
- 檔案分析
- 逆向工程
- 資安研究
- Binary inspection 與實驗用途

---

## 功能特色
- 取得檔案大小
- 顯示前 16 位元組（Magic bytes）
- 基本檔案類型識別（ELF、PE、PDF、ZIP、PNG、JPEG 等）
- SHA-256 雜湊計算（自行實作，無外部函式庫）
- Shannon 熵值計算（可用於判斷壓縮或封裝檔案）

---

## 編譯方式
```bash
make
````

## 使用方式

```bash
./build/bininspect <file>
```

---

## 設計原則

* 使用標準 C（C11）
* 不使用任何 OS 或平台專用 API
* 不直接將檔案映射到結構體
* 所有資料皆透過安全的位元組讀取與轉換處理
* 適合作為後續工具或研究的基礎模組

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

The goal of this project is to provide a small, portable and extensible
foundation for:

* File analysis
* Reverse engineering
* Security research
* Binary inspection and experimentation

---

## Features

* File size inspection
* First 16 bytes display (magic bytes)
* Basic file type detection (ELF, PE, PDF, ZIP, PNG, JPEG, etc.)
* SHA-256 hashing (custom implementation, no external libraries)
* Shannon entropy calculation (useful for detecting compression or packing)

---

## Build

```bash
make
```

## Usage

```bash
./build/bininspect <file>
```

---

## Design Principles

* Standard C (C11)
* No OS- or platform-specific APIs
* No direct struct mapping of file contents
* Safe byte-level reading and conversion
* Intended as a base for further tooling or research

---

## License

This project is released under the **MIT License**.
You are free to use, modify, distribute and fork it without restrictions.
