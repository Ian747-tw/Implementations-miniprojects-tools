# Repository Guidelines

## Project Structure & Module Organization
- Root files: `main.cpp`, `func.hpp`, `read_file.cpp`, `criteo_1000.txt`, `README.md`.
- Data files are tab-delimited and include 23 fields (with 7 product category columns).
- Primary executable for grading is expected to be `demo` (built by Makefile).

## Build, Test, and Development Commands
- `make`: build the `demo` executable (required by the spec).
- Example run: `./demo /path/to/data/file` (the TA provides the file path).
- Manual build (local check): `g++ -std=c++17 -O2 -Wall main.cpp -o main`.

## Coding Style & Naming Conventions
- Language: C++17.
- Indentation: 2 or 4 spaces, keep it consistent within a file.
- Naming: use `snake_case` for variables and functions; keep types and constants clear.
- Prefer explicit types for performance-critical data structures (e.g., `std::vector<int>`).

## Testing Guidelines
- No automated tests in the repository yet.
- Validate locally by running `./demo` with a known dataset and entering commands:
  - `get u p t`
  - `purchased u`
  - `clicked p1 p2`
  - `profit t θ`
  - `quit`

## Input/Output Contract (TA Spec)
- Program reads a data file path from argv: `./demo /path/to/data/file`.
- Input file has 23 tab-separated fields; product categories span 7 columns.
- Output for each query is wrapped by 20 `*` characters on separate lines.
- Sorting rules:
  - `purchased`: sort by `product_id`, then `click_timestamp` (ascending).
  - `clicked`: sort by `user_id` (ascending).
  - `profit`: output first 10 `user_id` sorted (ascending), timestamps inclusive.

## Commit & Pull Request Guidelines
- Keep commit subjects short and imperative (e.g., `update README.md`).
- PRs should describe the change, list affected files, and include sample commands or
  outputs when behavior changes.
