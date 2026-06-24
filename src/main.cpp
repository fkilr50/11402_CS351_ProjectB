#include <exception>
#include <iostream>
#include <string>

#include "csv_engine.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: engine \"SELECT columns FROM file.csv WHERE condition\"\n";
    return 1;
  }

  try {
    const csvdb::Query query = csvdb::ParseQuery(argv[1]);
    const csvdb::Table table = csvdb::LoadCsv(query.filename);
    const csvdb::QueryResult result = csvdb::ExecuteQuery(table, query);

    std::cout << csvdb::FormatCsv(result);
    std::cout << "\n" << result.rows.size() << " row(s) matched.\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << "\n";
    return 1;
  }
}
