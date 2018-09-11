// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

/*
 * Copyright ©2017 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Autumn Quarter 2017 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;

namespace hw4 {

bool HttpConnection::GetNextRequest(HttpRequest *request) {
  // Use "WrappedRead" to read data into the buffer_
  // instance variable.  Keep reading data until either the
  // connection drops or you see a "\r\n\r\n" that demarcates
  // the end of the request header.
  //
  // Once you've seen the request header, use ParseRequest()
  // to parse the header into the *request argument.
  //
  // Very tricky part:  clients can send back-to-back requests
  // on the same socket.  So, you need to preserve everything
  // after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!

  // MISSING:
  // Use std::string::find to find "\r\n\r\n"
  size_t foundpos = buffer_.find("\r\n\r\n");
  if (foundpos != std::string::npos) {  // "\r\n\r\n" is found in buffer_
    *request = ParseRequest(foundpos + 4);
  } else {
    unsigned char buf[1024];
    while (1) {
      int res = WrappedRead(fd_, buf, 1024);
      if (res == -1) {
        // Failure on Read
        return false;
      } else if (res == 0) {
        // Connection drops
        break;
      } else {
        // Add data read into buffer_
        buffer_ += std::string(reinterpret_cast<char*> (buf), res);

        // Break if find "\r\n\r\n"
        foundpos = buffer_.find("\r\n\r\n");
        if(foundpos != std::string::npos)
          break;
      }
    }
    *request = ParseRequest(foundpos + 4);
  }

  // Invalid request
  if (request->URI == "INVALID") {
    request = nullptr;
    return false;
  }

  // Preserve everything after the "\r\n\r\n" into buffer_
  buffer_ = buffer_.substr(foundpos + 4);

  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse &response) {
  std::string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         (unsigned char *) str.c_str(),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(size_t end) {
  HttpRequest req;
  req.URI = "/";  // by default, get "/".

  // Get the header.
  std::string str = buffer_.substr(0, end);

  // Split the header into lines.  Extract the URI from the first line
  // and store it in req.URI.  For each additional line beyond the
  // first, extract out the header name and value and store them in
  // req.headers (i.e., req.headers[headername] = headervalue).
  // You should look at HttpResponse.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for (a) splitting
  // a string into lines on a "\r\n" delimiter, (b) trimming
  // whitespace from the end of a string, and (c) converting a string
  // to lowercase.

  // MISSING:
  // Use boost::split to split the string into lines on  a "\r\n" delimiter
  std::vector<std::string> lines;
  boost::split(lines, str, boost::is_any_of("\r\n"),
               boost::token_compress_on);

  // Check the requst format
  if (lines.size() < 2) {
    req.URI = "INVALID";
  }

  // Trim white space from the end of a string.
  for (size_t i = 0; i < lines.size(); i++) {
    boost::trim(lines[i]);
  }

  // Extract the URI from the first line and store it in req.URI
  // Split first line.
  std::vector<std::string> firstline;
  boost::split(firstline, lines[0], boost::is_any_of(" "),
               boost::token_compress_on);
  // The format of first line should be like
  // [METHOD] [request-uri] HTTP/[version]\r\n
  // Here we only handle GET method.
  if (firstline.size() == 3 &&
      firstline[0] == "GET" &&
      firstline[1][0] == '/' &&
      firstline[2].find("HTTP/") != std::string::npos) {
    req.URI = firstline[1];
  } else {
    req.URI = "INVALID";
    return req;
  }

  // Extract the header name and value, store them into req.header
  for (size_t i = 1; i < lines.size() - 1; i++) {
    size_t foundpos = lines[i].find(": ");

    // Check the format contains ": "
    if (foundpos == std::string::npos) {
      req.URI = "INVALID";
      return req;
    }

    // Extract the hader name and value, convert header name to lowercase
    std::string headername = lines[i].substr(0, foundpos);
    boost::to_lower(headername);
    std::string headervalue = lines[i].substr(foundpos + 2);
    req.headers[headername] = headervalue;
  }

  return req;
}

}  // namespace hw4
