#include <chrono>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#include "csv_engine.h"

#ifndef TEST_DATA_PATH
#define TEST_DATA_PATH "data/movies.csv"
#endif

namespace {

int tests_passed = 0;
int tests_failed = 0;

void Check(bool condition, const std::string& name) {
  if (condition) {
    ++tests_passed;
    std::cout << "PASS: " << name << '\n';
  } else {
    ++tests_failed;
    std::cerr << "FAIL: " << name << '\n';
  }
}

void ExpectThrows(const std::function<void()>& action, const std::string& name) {
  try {
    action();
    Check(false, name);
  } catch (const std::exception&) {
    Check(true, name);
  }
}

std::string QueryWithFile(const std::string& selection,
                          const std::string& condition) {
  return "SELECT " + selection + " FROM " + TEST_DATA_PATH + " WHERE " + condition;
}

}  // namespace

int main() {
  const csvdb::Table table = csvdb::LoadCsv(TEST_DATA_PATH);

  Check(table.headers.size() == 5, "loads five CSV columns");
  Check(table.rows.size() == 15, "loads all movie rows");
  Check(table.rows.back().front() == "Good Morning, Vietnam",
        "parses a quoted field containing a comma");

  {
    const csvdb::Query query = csvdb::ParseQuery(
        QueryWithFile("title, rating", "year > 2000"));
    const csvdb::QueryResult result = csvdb::ExecuteQuery(table, query);
    Check(result.headers.size() == 2 && result.headers[0] == "title" &&
              result.headers[1] == "rating",
          "projects selected columns");
    Check(result.rows.size() == 10, "filters numeric values");
  }

  {
    const csvdb::Query query = csvdb::ParseQuery(
        QueryWithFile("title", "genre = Animation"));
    const csvdb::QueryResult result = csvdb::ExecuteQuery(table, query);
    Check(result.rows.size() == 2, "filters string values");
  }

  {
    const csvdb::Query query = csvdb::ParseQuery(
        QueryWithFile("*", "rating >= 9.0"));
    const csvdb::QueryResult result = csvdb::ExecuteQuery(table, query);
    Check(result.headers.size() == table.headers.size() && result.rows.size() == 2,
          "supports wildcard selection");
  }

  {
    const csvdb::Query query = csvdb::ParseQuery(
        QueryWithFile("title", "title = 'Good Morning, Vietnam'"));
    const csvdb::QueryResult result = csvdb::ExecuteQuery(table, query);
    Check(result.rows.size() == 1 && result.rows[0][0] == "Good Morning, Vietnam",
          "supports a quoted query value");
    Check(csvdb::FormatCsv(result).find("\"Good Morning, Vietnam\"") != std::string::npos,
          "escapes commas in output CSV");
  }

  {
    const csvdb::Query query = csvdb::ParseQuery(
        QueryWithFile("title", "year > 2030"));
    const csvdb::QueryResult result = csvdb::ExecuteQuery(table, query);
    Check(result.rows.empty() && result.headers.size() == 1,
          "returns headers when no rows match");
  }

  ExpectThrows(
      [&table]() {
        const csvdb::Query query = csvdb::ParseQuery(
            QueryWithFile("missing_column", "year > 2000"));
        static_cast<void>(csvdb::ExecuteQuery(table, query));
      },
      "rejects an unknown selected column");

  ExpectThrows(
      [&table]() {
        const csvdb::Query query = csvdb::ParseQuery(
            QueryWithFile("title", "rating > excellent"));
        static_cast<void>(csvdb::ExecuteQuery(table, query));
      },
      "rejects non-numeric values for numeric columns");

  ExpectThrows(
      []() {
        static_cast<void>(csvdb::ParseQuery("SELECT title movies.csv"));
      },
      "rejects invalid query syntax");

  ExpectThrows(
      []() {
        static_cast<void>(csvdb::LoadCsv("missing-file.csv"));
      },
      "reports a missing CSV file");

  {
    csvdb::Table large_table;
    large_table.headers = {"id", "title", "rating"};
    large_table.rows.reserve(10000);
    for (int index = 0; index < 10000; ++index) {
      large_table.rows.push_back(
          {std::to_string(index), "Movie " + std::to_string(index), "8.0"});
    }

    const csvdb::Query query = csvdb::ParseQuery(
        "SELECT title FROM generated.csv WHERE id >= 9000");
    const auto start = std::chrono::steady_clock::now();
    const csvdb::QueryResult result = csvdb::ExecuteQuery(large_table, query);
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);

    Check(result.rows.size() == 1000 && elapsed.count() < 500,
          "processes 10,000 rows in under 500 ms");
  }

  const int total = tests_passed + tests_failed;
  std::cout << "\n" << tests_passed << "/" << total << " tests passed.\n";
  return tests_failed == 0 ? 0 : 1;
}
