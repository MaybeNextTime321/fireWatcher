# Asset Validation Tool

## Overview

Asset Validation Tool is a C++ developer utility for scanning and validating large game asset repositories.  
The project is designed as a modular validation pipeline for technical designers, tools programmers, and engine teams.

It focuses on detecting common content issues early in development and enabling automated validation in CI pipelines.

---

## Features

### File Scanner
- Recursive directory traversal using std::filesystem
- Directory filtering (blocked paths)
- File extension filtering (blocked formats)
- Clean and extensible API for validation pipelines

### Planned Modules
- Lang Duplicate Checker  
  Detects duplicate localization keys in .lang files
- JSON ID Duplicate Checker  
  Detects duplicate IDs in structured JSON asset definitions
- JSON Schema Validator  
  Validates JSON assets against defined schemas
- Report Generator  
  Exports validation results in JSON or text format for CI pipelines

---

## Architecture

The tool follows a modular pipeline design:

FileScanner -> Analyzer Modules -> Report Generator

Each validation module is independent and reusable, allowing easy extension with new asset checks.

---

## Tech Stack

- C++17
- std::filesystem
- CMake build system
- Cross-platform (Windows and Linux)
- Designed for large-scale game asset repositories

---

## Example Usage

asset_validator scan --root ./assets --json-only  
asset_validator check-lang --path ./localization  
asset_validator validate-json --schema schema.json  

---

## Project Structure

/src  
    FileScanner  
    LangChecker  
    JsonIdChecker  
    SchemaValidator  

/config  
    blocked_paths.json  
    blocked_formats.json  

/tools  
    report_generator  

---

## Goals

- Automate validation of game assets
- Prevent duplicate localization keys and asset IDs
- Detect malformed JSON asset files early
- Integrate asset validation into CI pipelines
- Serve as a portfolio project for tools and engine programming

---

## Motivation

Large game projects often suffer from:
- Duplicate localization keys
- Conflicting asset IDs
- Invalid or broken JSON asset definitions
- Manual validation errors

This tool automates asset validation and reduces content-related bugs.

---

## Build Instructions

git clone https://github.com/yourname/asset-validation-tool  
cd asset-validation-tool  
mkdir build  
cd build  
cmake ..  
cmake --build .  

---

## Roadmap

v0.1 (Done)  
- File system scanner  
- Directory and format filtering  

v0.2  
- Localization duplicate key checker  
- JSON ID duplicate checker  

v0.3  
- JSON schema validation  
- Validation report export  

v1.0  
- CLI interface  
- CI integration examples  
- Performance optimizations  

---

## License

MIT License

---

## Author

Ilia (Maybe) Rybakov  
Technical Game Designer transitioning to Tools and Engine Programming
