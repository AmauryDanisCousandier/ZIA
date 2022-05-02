# B-YEP-500_zia

The goal of the Zia project is to create an HTTP server. This server will be able to serve typical HTTP doc-
uments and page requests, as well as CGI execution and more. The server MUST be written in C++, with
support for interoperable modules.

You can add plugins via the specified API documentation ./doc/api.txt

## Installation

mkdir build && cd build && conan install .. --build=missing &&
cmake .. -G “Unix Makefiles” && cmake --build .

## Usage

probably ./binary