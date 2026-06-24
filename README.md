# CSV Mini Database and Query Engine

Project B is a small C++ command-line program that loads a CSV file and executes
one simple SQL-like query against it.

## Implementation Status

The required query engine is implemented with C++20. The repository includes:

- A command-line executable named `engine`.
- A reusable CSV/query engine library.
- A 15-row `movies.csv` example dataset.
- Automated tests for parsing, filtering, projection, CSV quoting, errors, and
  the 10,000-row performance target.

## Quick Start

With CMake:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the sample query from the repository root:

```bash
./build/engine "SELECT title, rating FROM data/movies.csv WHERE year > 2000"
```

On Windows with MinGW `g++` and no CMake:

```powershell
New-Item -ItemType Directory -Force build
g++ -std=c++20 -Wall -Wextra -Wpedantic -Iinclude src\main.cpp src\csv_engine.cpp -o build\engine.exe
g++ -std=c++20 -Wall -Wextra -Wpedantic -Iinclude tests\test_engine.cpp src\csv_engine.cpp -o build\csv_engine_tests.exe
build\csv_engine_tests.exe
build\engine.exe "SELECT title, rating FROM data/movies.csv WHERE year > 2000"
```

The handwritten project specification is the source of truth for this repo. This
README intentionally describes only the required scope from that specification.

## Goal

Build a lightweight query engine that can:

- Load data from a CSV file.
- Accept one query as a command-line argument.
- Parse a simple `SELECT ... FROM ... WHERE ...` query.
- Return only the requested columns.
- Filter rows using one comparison condition.
- Print useful error messages for invalid queries or CSV problems.

Example query:

```sql
SELECT title, rating FROM movies.csv WHERE year > 2000
```

Example CLI usage:

```bash
./engine "SELECT title, rating FROM movies.csv WHERE year > 2000"
```

## Supported Query Format

The required query format is:

```sql
SELECT [column-names] FROM [filename] WHERE [column] [operator] [value]
```

The selected columns may be comma-separated:

```sql
SELECT title, rating FROM movies.csv WHERE year > 2000
```

Selecting every column may also be supported:

```sql
SELECT * FROM movies.csv WHERE rating >= 8.0
```

Supported comparison operators:

- `=`
- `!=`
- `<`
- `>`
- `<=`
- `>=`

## Expected Errors

The program should report an error instead of crashing when it receives bad
input, such as:

- Misspelled column names.
- Missing query values.
- Incorrect query syntax.
- Missing or unreadable CSV files.
- Invalid comparisons between incompatible values.

## Design

Implemented components:

- `main`: handles command-line input and controls the program flow.
- `CSVLoader`: reads the CSV file into memory.
- `Parser`: breaks the raw query string into usable parts.
- `QueryEngine`: decides how to execute the parsed query.
- `TypeConverter`: converts CSV text to numbers when numeric comparison is
  needed.
- `ResultSet`: stores matching rows and prints the result.

## Project Structure

```text
.
|-- CMakeLists.txt
|-- data/
|   `-- movies.csv
|-- include/
|   `-- csv_engine.h
|-- src/
|   |-- csv_engine.cpp
|   `-- main.cpp
`-- tests/
    `-- test_engine.cpp
```

## Performance Requirement

For a mini database, a CSV file with at most about 10,000 rows should be
processed in under 500 ms. Larger datasets should still work when possible, but
they are not the main performance target.

## Testing

The custom test executable currently checks:

- Valid queries with matching rows.
- Valid queries with no matches.
- Selecting one column, multiple columns, and `*`.
- Numeric comparisons such as `year > 2000`.
- String comparisons such as `title = Inception`.
- Invalid syntax.
- Unknown column names.
- Missing files.
- Quoted CSV fields containing commas.
- A 10,000-row in-memory query completing in under 500 ms.

## Out of Scope

The spec does not require full SQL support. These features are not part of the
core goal unless added later on purpose:

- Joins.
- Aggregation functions.
- `GROUP BY`.
- `ORDER BY`.
- `INSERT`, `UPDATE`, or `DELETE`.
- Indexing.
- Multiple simultaneous tables.
- A graphical or web UI.
