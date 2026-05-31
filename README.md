# CSV Mini Database and Query Engine

Project B is a small C++ command-line program that loads a CSV file and executes
one simple SQL-like query against it.

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

Planned components:

- `main`: handles command-line input and controls the program flow.
- `CSVLoader`: reads the CSV file into memory.
- `Parser`: breaks the raw query string into usable parts.
- `QueryEngine`: decides how to execute the parsed query.
- `TypeConverter`: converts CSV text to numbers when numeric comparison is
  needed.
- `ResultSet`: stores matching rows and prints the result.

## Performance Requirement

For a mini database, a CSV file with at most about 10,000 rows should be
processed in under 500 ms. Larger datasets should still work when possible, but
they are not the main performance target.

## Testing

Testing will focus on the movies dataset mentioned in the project notes.
Important cases include:

- Valid queries with matching rows.
- Valid queries with no matches.
- Selecting one column, multiple columns, and `*`.
- Numeric comparisons such as `year > 2000`.
- String comparisons such as `title = Inception`.
- Invalid syntax.
- Unknown column names.
- Missing files.

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
