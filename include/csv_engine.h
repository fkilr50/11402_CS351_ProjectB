#ifndef CSV_ENGINE_H_
#define CSV_ENGINE_H_

#include <cstddef>
#include <string>
#include <vector>

namespace csvdb {

struct Query {
  std::vector<std::string> selected_columns;
  std::string filename;
  std::string where_column;
  std::string comparison_operator;
  std::string comparison_value;
  bool select_all = false;
};

struct Table {
  std::vector<std::string> headers;
  std::vector<std::vector<std::string>> rows;
};

struct QueryResult {
  std::vector<std::string> headers;
  std::vector<std::vector<std::string>> rows;
};

Query ParseQuery(const std::string& query_text);
Table LoadCsv(const std::string& filename);
QueryResult ExecuteQuery(const Table& table, const Query& query);
std::string FormatCsv(const QueryResult& result);

}  // namespace csvdb

#endif  // CSV_ENGINE_H_
