# CSV Mini Database with Query Engine

A lightweight, in-memory database engine that supports CSV file operations and a custom query language for data manipulation and retrieval.

## Overview

This project implements a small but functional database system that allows you to:
- Load and manage CSV data in memory
- Execute custom queries on datasets
- Perform filtering, projection, and aggregation operations
- Support for basic SQL-like operations without requiring a full database

## Features

✨ **CSV File Management**
- Load CSV files into memory
- Support for multiple tables/datasets simultaneously
- Automatic schema inference from CSV headers
- Handle various data types (strings, integers, floats, dates)

🔍 **Query Engine**
- SELECT operations with column projection
- WHERE clause filtering with various predicates
- JOIN operations between tables
- Aggregation functions (COUNT, SUM, AVG, MAX, MIN)
- GROUP BY and HAVING clauses
- ORDER BY sorting
- LIMIT and OFFSET pagination

📊 **Data Operations**
- INSERT new records
- UPDATE existing records
- DELETE records by condition
- Index creation for optimized queries

## Project Structure

```
11402_CS351_ProjectB/
├── README.md              # Project documentation
├── src/
│   ├── __init__.py
│   ├── csv_loader.py      # CSV file loading and parsing
│   ├── table.py           # Table representation and operations
│   ├── query_engine.py    # Query parser and executor
│   ├── query_parser.py    # Query tokenization and parsing
│   └── main.py            # CLI entry point
├── tests/
│   ├── __init__.py
│   ├── test_csv_loader.py
│   ├── test_query_engine.py
│   └── test_table.py
├── examples/
│   ├── sample_data.csv    # Sample CSV file
│   └── usage_examples.py  # Usage demonstrations
└── requirements.txt       # Project dependencies
```

## Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/fkilr50/11402_CS351_ProjectB.git
   cd 11402_CS351_ProjectB
   ```

2. **Install dependencies**
   ```bash
   pip install -r requirements.txt
   ```

3. **Verify installation**
   ```bash
   python -m pytest tests/
   ```

## Quick Start

### Basic Usage

```python
from src.csv_loader import CSVLoader
from src.query_engine import QueryEngine

# Load a CSV file
loader = CSVLoader()
table = loader.load('data.csv')

# Create query engine
engine = QueryEngine()
engine.register_table('users', table)

# Execute a simple query
results = engine.query("SELECT name, email FROM users WHERE age > 18")
print(results)
```

### Running the CLI

```bash
python src/main.py --load data.csv --query "SELECT * FROM data"
```

## Query Syntax

### SELECT Queries

**Basic Selection:**
```sql
SELECT name, age FROM users
```

**With WHERE Clause:**
```sql
SELECT * FROM users WHERE age > 25 AND city = 'New York'
```

**With Aggregation:**
```sql
SELECT city, COUNT(*) as total FROM users GROUP BY city
```

**With Ordering and Limit:**
```sql
SELECT name, salary FROM employees ORDER BY salary DESC LIMIT 10
```

### Supported Operators

- **Comparison**: `=`, `!=`, `<`, `>`, `<=`, `>=`
- **Logical**: `AND`, `OR`, `NOT`
- **String**: `LIKE` (pattern matching), `IN` (list membership)
- **Aggregate Functions**: `COUNT`, `SUM`, `AVG`, `MIN`, `MAX`

### JOIN Operations

```sql
SELECT u.name, o.order_id FROM users u
JOIN orders o ON u.id = o.user_id
WHERE o.total > 100
```

### Data Modification

**Insert:**
```sql
INSERT INTO users (name, email, age) VALUES ('John Doe', 'john@example.com', 30)
```

**Update:**
```sql
UPDATE users SET age = 31 WHERE id = 1
```

**Delete:**
```sql
DELETE FROM users WHERE age < 18
```

## Architecture

### Components

1. **CSV Loader (`csv_loader.py`)**
   - Handles CSV parsing and loading
   - Infers column types
   - Manages data normalization

2. **Table (`table.py`)**
   - In-memory table representation
   - Row and column operations
   - Basic indexing support

3. **Query Parser (`query_parser.py`)**
   - Tokenizes query strings
   - Builds abstract syntax tree (AST)
   - Validates query syntax

4. **Query Engine (`query_engine.py`)**
   - Executes parsed queries
   - Manages multiple tables
   - Handles joins and aggregations

## Examples

### Example 1: Loading and Querying Sales Data

```python
from src.csv_loader import CSVLoader
from src.query_engine import QueryEngine

loader = CSVLoader()
sales = loader.load('sales.csv')

engine = QueryEngine()
engine.register_table('sales', sales)

# Find top 5 customers by spending
top_customers = engine.query("""
    SELECT customer_id, SUM(amount) as total_spending
    FROM sales
    GROUP BY customer_id
    ORDER BY total_spending DESC
    LIMIT 5
""")
```

### Example 2: Data Filtering and Analysis

```python
# Find all orders from 2024
recent_orders = engine.query("""
    SELECT * FROM sales
    WHERE date >= '2024-01-01'
    ORDER BY date DESC
""")

# Get statistics
summary = engine.query("""
    SELECT 
        COUNT(*) as total_orders,
        AVG(amount) as avg_order_value,
        MAX(amount) as max_order,
        MIN(amount) as min_order
    FROM sales
""")
```

## Performance Considerations

- Queries are executed in-memory for fast access
- Index creation on frequently queried columns improves performance
- Large datasets (>1GB) may require optimization
- Consider data caching for repeated queries

## Limitations

- Single-threaded query execution
- No transaction support
- Limited to in-memory storage
- No built-in authentication or access control
- Complex nested queries may have performance impact

## Testing

Run the test suite to verify functionality:

```bash
# Run all tests
pytest tests/

# Run with coverage
pytest --cov=src tests/

# Run specific test file
pytest tests/test_query_engine.py -v
```

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Roadmap

- [ ] Multi-threaded query execution
- [ ] Transaction support (ACID compliance)
- [ ] B-tree indexing for better query performance
- [ ] Support for more complex joins (LEFT JOIN, RIGHT JOIN, FULL OUTER JOIN)
- [ ] Query optimization and execution plans
- [ ] Export functionality (to JSON, Parquet, etc.)
- [ ] Web UI for query execution
- [ ] Caching layer for frequently accessed data

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

**Developer**: fkilr50  
**Course**: AI Software (CS351)  
**Institution**: University Project  
**Semester**: 6

## Contact

For questions or suggestions, please open an issue on the GitHub repository.

---

**Last Updated**: April 2026