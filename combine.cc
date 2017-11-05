#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <exception>
#include "json.hpp"

/*

Combine all json with the following template:
{
  "authors": ["Nguyen Van A", "Tran Van B", "Nguyen Thi C"],
  "modified": "03/10/2017 - 22:40:00",
  "collection": [
    {"query": "Các giải thuật sắp xếp",
      "description": "Muốn tìm hiểu về giải thuật sắp xếp, bất kỳ trang web nào cung cấp thông tin về giải thuật sắp xếp: tổng hợp các giải thuật sắp xếp, giải thích về một giải thuật sắp cụ thể, hướng dẫn cài đặt giải thuật sắp xếp trên một ngôn ngữ lập trình đều là kết quả phù hợp.",
      "sites": [
          {"url": "https://vi.wikipedia.org/wiki/Thu%E1%BA%ADt_to%C3%A1n_s%E1%BA%AFp_x%E1%BA%BFp",
          "title": "Thuật toán sắp xếp – Wikipedia tiếng Việt",
          "content": "Điểm khác biệt giữa sắp xếp nhanh và sắp xếp trộn là trong sắp xếp trộn việc xác định thứ tự được xác định khi \"trộn\"",
          "relevance": "yes"
          }
        ]
    }
  ]
}

into a final data collection with the following requirements:
  + authors should be saved
  + modified should be saved
  + queries and theirs descriptions should be taken into a seperated collection
  + sites should be taken into a seperated collection
  + query - document relevance should be taken into a seperated collection
  + every unique query should have an unique id
  + every unique site should have an unique id
  + every assessment should have an unique id

the target json may have the following structure v.1.0:
  {
    "combined": "${timestamp}",
    "queries": [
      {
        "id": "${unique query id}",
        "authors": ["${authors list}"],
        "modified": "${timestamp}",
        "query": "query text as will be provided in the search engine",
        "description": "detail description for information need for this query and what should be relevance"
      }
    ],
    "documents": [
      {
        "id": "${unique document id}",
        "authors": ["${authors list}"],
        "modified": "${timestamp}",
        "url": "https://document.url",
        "title": "document title",
        "content": "Extracted texts from the document"
      }
    ],
    "relevances": [
      {
        "id": "${unique assessment id}",
        "authors": ["${authors list}"],
        "modified": "${timestamp}",
        "docid": "${unique document id}",
        "queryid": "${unique query id}",
        "yes": "${boolean}"
      }
    ]
  }
*/

using json = nlohmann::json;

int g_qid = 0;
int g_did = 0;
int g_rid = 0;

bool Merge(const json& j, json& all) {
  json authors = j["authors"];
  std::string modified = j["modified"];
  const json& c = j["collection"];
  json& queries = all["queries"];
  json& documents = all["documents"];
  json& relevances = all["relevances"];

  for (const auto& it: c) {
    json q;
    q["authors"] = authors;
    q["id"] = g_qid++;
    q["modified"] = modified;
    q["query"] = it["query"];
    q["description"] = it["description"];
    queries.push_back(q);

    const json& sites = it["sites"];
    for (const auto& s: sites) {
      json d;
      d["id"] = g_did++;
      d["authors"] = authors;
      d["modified"] = modified;
      d["url"] = s["url"];
      d["title"] = s["title"];
      d["content"] = s["content"];
      documents.push_back(d);

      json r;
      r["id"] = g_rid++;
      r["authors"] = authors;
      r["modified"] = modified;
      r["docid"] = d["id"];
      r["queryid"] = q["id"];
      r["yes"] = (s["relevance"] == "yes") || (s["relevance"] == "1") 
                  || (s["relevance"] == 1);
      relevances.push_back(r);
    }
  }
  return true;
}

std::string GetTimeStampt() {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::ostringstream o;
  o << std::put_time(std::localtime(&now_c), "%d/%m/%Y - %H:%M");
  return o.str();
}

int main(int argc, char* argv[]) {
  json all;
  
  for (int i = 1; i < argc; ++i) {
    // We dont handle errors here, so please make sure that all input
    //  file names are correct
    std::ifstream input(argv[i]);
    json j;
    input >> j;
    Merge(j, all);
  }

  all["combined"] = GetTimeStampt();
  std::cout << all.dump(2) << std::endl;
}
