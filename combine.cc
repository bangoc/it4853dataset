#include <iostream>
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
        "last modified": "${timestamp}",
        "query": "query text as will be provided in the search engine",
        "description": "detail description for information need for this query and what should be relevance"
      }
    ],
    "documents": [
      {
        "id": "${unique document id}",
        "authors": ["${authors list}"],
        "last modified": "${timestamp}",
        "url": "https://document.url",
        "title": "document title",
        "content": "Extracted texts from the document"
      }
    ],
    "assessments": [
      {
        "id": "${unique assessment id}",
        "authors": ["${authors list}"],
        "last modified": "${timestamp}",
        "docid": "${unique document id}",
        "queryid": "${unique query id}",
        "relevance": "${boolean}"
      }
    ]
  }
*/

using json = nlohmann::json;

int main(int argc, char* argv[]) {
  json all = 
  R"({
    "combined": "${timestamp}",
    "queries": [
      {
        "id": "${unique query id}",
        "authors": ["${authors list}"],
        "last modified": "${timestamp}",
        "query": "query text as will be provided in the search engine",
        "description": "detail description for information need for this query and what should be relevance"
      }
    ],
    "documents": [
      {
        "id": "${unique document id}",
        "authors": ["${authors list}"],
        "last modified": "${timestamp}",
        "url": "https://document.url",
        "title": "document title",
        "content": "Extracted texts from the document"
      }
    ],
    "assessments": [
      {
        "id": "${unique assessment id}",
        "authors": ["${authors list}"],
        "last modified": "${timestamp}",
        "docid": "${unique document id}",
        "queryid": "${unique query id}",
        "relevance": "${boolean}"
      }
    ]
  })"_json;
  std::cout << all.dump(2) << std::endl;
}
