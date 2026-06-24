#include "csv_engine.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace csvdb {
namespace {

std::string Trim(const std::string& value) {
  const auto first = std::find_if_not(value.begin(), value.end(), [](unsigned char ch) {
    return std::isspace(ch);
  });
  const auto last = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char ch) {
    return std::isspace(ch);
  }).base();

  if (first >= last) {
    return "";
  }
  return std::string(first, last);
}

std::string StripQuotes(const std::string& value) {
  if (value.size() >= 2 &&
      ((value.front() == '"' && value.back() == '"') ||
       (value.front() == '\'' && value.back() == '\''))) {
    return value.substr(1, value.size() - 2);
  }
  return value;
}

std::vector<std::string> SplitSelectedColumns(const std::string& text) {
  std::vector<std::string> columns;
  std::stringstream stream(text);
  std::string column;

  while (std::getline(stream, column, ',')) {
    column = Trim(column);
    if (column.empty()) {
      throw std::runtime_error("Selected column names cannot be empty.");
    }
    columns.push_back(column);
  }

  if (columns.empty()) {
    throw std::runtime_error("At least one selected column is required.");
  }
  return columns;
}

std::vector<std::string> ParseCsvRow(const std::string& line) {
  std::vector<std::string> fields;
  std::string field;
  bool in_quotes = false;

  for (std::size_t index = 0; index < line.size(); ++index) {
    const char ch = line[index];

    if (ch == '"') {
      if (in_quotes && index + 1 < line.size() && line[index + 1] == '"') {
        field.push_back('"');
        ++index;
      } else {
        in_quotes = !in_quotes;
      }
    } else if (ch == ',' && !in_quotes) {
      fields.push_back(Trim(field));
      field.clear();
    } else {
      field.push_back(ch);
    }
  }

  if (in_quotes) {
    throw std::runtime_error("CSV contains an unterminated quoted field.");
  }

  fields.push_back(Trim(field));
  return fields;
}

std::optional<double> ParseNumber(const std::string& value) {
  const std::string trimmed = Trim(value);
  if (trimmed.empty()) {
    return std::nullopt;
  }

  std::size_t consumed = 0;
  try {
    const double number = std::stod(trimmed, &consumed);
    if (consumed == trimmed.size() && std::isfinite(number)) {
      return number;
    }
  } catch (const std::exception&) {
    return std::nullopt;
  }
  return std::nullopt;
}

bool CompareNumbers(double left, double right, const std::string& operation) {
  if (operation == "=") return left == right;
  if (operation == "!=") return left != right;
  if (operation == "<") return left < right;
  if (operation == ">") return left > right;
  if (operation == "<=") return left <= right;
  if (operation == ">=") return left >= right;
  throw std::runtime_error("Unsupported comparison operator: " + operation);
}

bool CompareStrings(const std::string& left, const std::string& right,
                    const std::string& operation) {
  if (operation == "=") return left == right;
  if (operation == "!=") return left != right;
  if (operation == "<") return left < right;
  if (operation == ">") return left > right;
  if (operation == "<=") return left <= right;
  if (operation == ">=") return left >= right;
  throw std::runtime_error("Unsupported comparison operator: " + operation);
}

std::size_t RequireColumn(
    const std::unordered_map<std::string, std::size_t>& column_indices,
    const std::string& column) {
  const auto found = column_indices.find(column);
  if (found == column_indices.end()) {
    throw std::runtime_error("Unknown column: " + column);
  }
  return found->second;
}

std::string EscapeCsvField(const std::string& field) {
  if (field.find_first_of(",\"\n\r") == std::string::npos) {
    return field;
  }

  std::string escaped = "\"";
  for (const char ch : field) {
    if (ch == '"') {
      escaped += "\"\"";
    } else {
      escaped.push_back(ch);
    }
  }
  escaped.push_back('"');
  return escaped;
}

void WriteCsvRow(std::ostringstream& output, const std::vector<std::string>& row) {
  for (std::size_t index = 0; index < row.size(); ++index) {
    if (index > 0) output << ',';
    output << EscapeCsvField(row[index]);
  }
  output << '\n';
}

}  // namespace

Query ParseQuery(const std::string& query_text) {
  static const std::regex pattern(
      R"(^\s*SELECT\s+(.+?)\s+FROM\s+(\S+)\s+WHERE\s+([A-Za-z_][A-Za-z0-9_]*)\s*(<=|>=|!=|=|<|>)\s*(.+?)\s*$)",
      std::regex::icase);

  std::smatch match;
  if (!std::regex_match(query_text, match, pattern)) {
    throw std::runtime_error(
        "Invalid query syntax. Expected: SELECT columns FROM file.csv WHERE column operator value");
  }

  Query query;
  const std::string selection = Trim(match[1].str());
  query.filename = StripQuotes(Trim(match[2].str()));
  query.where_column = Trim(match[3].str());
  query.comparison_operator = match[4].str();
  query.comparison_value = StripQuotes(Trim(match[5].str()));

  if (selection == "*") {
    query.select_all = true;
  } else {
    query.selected_columns = SplitSelectedColumns(selection);
  }

  if (query.filename.empty() || query.comparison_value.empty()) {
    throw std::runtime_error("Filename and comparison value cannot be empty.");
  }
  return query;
}

Table LoadCsv(const std::string& filename) {
  std::ifstream input(filename);
  if (!input.is_open()) {
    throw std::runtime_error("Could not open CSV file: " + filename);
  }

  std::string line;
  if (!std::getline(input, line)) {
    throw std::runtime_error("CSV file is empty: " + filename);
  }

  if (!line.empty() && line.back() == '\r') line.pop_back();
  Table table;
  table.headers = ParseCsvRow(line);

  if (table.headers.empty()) {
    throw std::runtime_error("CSV header row is empty.");
  }

  while (std::getline(input, line)) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    if (Trim(line).empty()) continue;

    std::vector<std::string> row = ParseCsvRow(line);
    if (row.size() != table.headers.size()) {
      throw std::runtime_error(
          "CSV row has " + std::to_string(row.size()) +
          " fields, but the header has " + std::to_string(table.headers.size()) + ".");
    }
    table.rows.push_back(std::move(row));
  }

  return table;
}

QueryResult ExecuteQuery(const Table& table, const Query& query) {
  std::unordered_map<std::string, std::size_t> column_indices;
  for (std::size_t index = 0; index < table.headers.size(); ++index) {
    if (!column_indices.emplace(table.headers[index], index).second) {
      throw std::runtime_error("Duplicate CSV column: " + table.headers[index]);
    }
  }

  const std::size_t where_index = RequireColumn(column_indices, query.where_column);
  std::vector<std::size_t> selected_indices;
  QueryResult result;

  if (query.select_all) {
    result.headers = table.headers;
    for (std::size_t index = 0; index < table.headers.size(); ++index) {
      selected_indices.push_back(index);
    }
  } else {
    result.headers = query.selected_columns;
    for (const std::string& column : query.selected_columns) {
      selected_indices.push_back(RequireColumn(column_indices, column));
    }
  }

  bool column_is_numeric = true;
  for (const auto& row : table.rows) {
    if (!row[where_index].empty() && !ParseNumber(row[where_index]).has_value()) {
      column_is_numeric = false;
      break;
    }
  }

  const std::optional<double> query_number = ParseNumber(query.comparison_value);
  if (column_is_numeric && !query_number.has_value()) {
    throw std::runtime_error(
        "Column '" + query.where_column + "' is numeric, but the query value is not numeric.");
  }

  for (const auto& row : table.rows) {
    bool matches = false;
    if (column_is_numeric) {
      const std::optional<double> row_number = ParseNumber(row[where_index]);
      matches = row_number.has_value() &&
                CompareNumbers(*row_number, *query_number, query.comparison_operator);
    } else {
      matches = CompareStrings(row[where_index], query.comparison_value,
                               query.comparison_operator);
    }

    if (!matches) continue;

    std::vector<std::string> projected_row;
    projected_row.reserve(selected_indices.size());
    for (const std::size_t index : selected_indices) {
      projected_row.push_back(row[index]);
    }
    result.rows.push_back(std::move(projected_row));
  }

  return result;
}

std::string FormatCsv(const QueryResult& result) {
  std::ostringstream output;
  WriteCsvRow(output, result.headers);
  for (const auto& row : result.rows) {
    WriteCsvRow(output, row);
  }
  return output.str();
}

}  // namespace csvdb
