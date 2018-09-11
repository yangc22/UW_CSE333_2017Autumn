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

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#include "./FileReader.h"
#include "./HttpConnection.h"
#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpServer.h"
#include "./libhw3/QueryProcessor.h"

using std::cerr;
using std::cout;
using std::endl;

namespace hw4 {

// Helper function that used to set the content type according to the suffix.
static void SetContentType(const std::string &suffix, HttpResponse *resp);

// This is the function that threads are dispatched into
// in order to process new client connections.
void HttpServer_ThrFn(ThreadPool::Task *t);

// Given a request, produce a response.
HttpResponse ProcessRequest(const HttpRequest &req,
                            const std::string &basedir,
                            const std::list<std::string> *indices);

// Process a file request.
HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir);

// Process a query request.
HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices);

bool HttpServer::Run(void) {
  // Create the server listening socket.
  int listen_fd;
  cout << "  creating and binding the listening socket..." << endl;
  if (!ss_.BindAndListen(AF_INET6, &listen_fd)) {
    cerr << endl << "Couldn't bind to the listening socket." << endl;
    return false;
  }

  // Spin, accepting connections and dispatching them.  Use a
  // threadpool to dispatch connections into their own thread.
  cout << "  accepting connections..." << endl << endl;
  ThreadPool tp(kNumThreads);
  while (1) {
    HttpServerTask *hst = new HttpServerTask(HttpServer_ThrFn);
    hst->basedir = staticfile_dirpath_;
    hst->indices = &indices_;
    if (!ss_.Accept(&hst->client_fd,
                    &hst->caddr,
                    &hst->cport,
                    &hst->cdns,
                    &hst->saddr,
                    &hst->sdns)) {
      // The accept failed for some reason, so quit out of the server.
      // (Will happen when kill command is used to shut down the server.)
      break;
    }
    // The accept succeeded; dispatch it.
    tp.Dispatch(hst);
  }
  return true;
}

void HttpServer_ThrFn(ThreadPool::Task *t) {
  // Cast back our HttpServerTask structure with all of our new
  // client's information in it.
  std::unique_ptr<HttpServerTask> hst(static_cast<HttpServerTask *>(t));
  cout << "  client " << hst->cdns << ":" << hst->cport << " "
       << "(IP address " << hst->caddr << ")" << " connected." << endl;

  bool done = false;
  // Use HttpConnection class
  HttpConnection hc(hst->client_fd);
  while (!done) {
    // Use the HttpConnection class to read in the next request from
    // this client, process it by invoking ProcessRequest(), and then
    // use the HttpConnection class to write the response.  If the
    // client sent a "Connection: close\r\n" header, then shut down
    // the connection.

    // MISSING:
    // Get next request
    HttpRequest req;
    if (!hc.GetNextRequest(&req)) {
      done = true;
      close(hst->client_fd);
    }

    // Process the request
    HttpResponse resp;
    resp = ProcessRequest(req, hst->basedir, hst->indices);

    // Write the response
    if (!hc.WriteResponse(resp)) {
      done = true;
      close(hst->client_fd);
    }

    // Close the connection if "Connection: close\r\n"
    if (req.headers["connection"] == "close") {
      done = true;
      close(hst->client_fd);
    }
  }
}

HttpResponse ProcessRequest(const HttpRequest &req,
                            const std::string &basedir,
                            const std::list<std::string> *indices) {
  // Is the user asking for a static file?
  if (req.URI.substr(0, 8) == "/static/") {
    return ProcessFileRequest(req.URI, basedir);
  }

  // The user must be asking for a query.
  return ProcessQueryRequest(req.URI, indices);
}


HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir) {
  // The response we'll build up.
  HttpResponse ret;

  // Steps to follow:
  //  - use the URLParser class to figure out what filename
  //    the user is asking for.
  //
  //  - use the FileReader class to read the file into memory
  //
  //  - copy the file content into the ret.body
  //
  //  - depending on the file name suffix, set the response
  //    Content-type header as appropriate, e.g.,:
  //      --> for ".html" or ".htm", set to "text/html"
  //      --> for ".jpeg" or ".jpg", set to "image/jpeg"
  //      --> for ".png", set to "image/png"
  //      etc.
  //
  // be sure to set the response code, protocol, and message
  // in the HttpResponse as well.
  std::string fname = "";

  // MISSING:
  // Use the URLParser class to figure out the filename
  URLParser urlparser;
  urlparser.Parse(uri);
  fname += urlparser.get_path();
  // Replace "/static/" with ""
  fname = fname.replace(0, 8, "");

  // Use the FileReader class to read the file into memory
  FileReader fr(basedir, fname);

  std::string filecontent;

  if (fr.ReadFile(&filecontent)) {
    // Get the suffix of file name and set the response.
    size_t dotpos = fname.rfind(".");  // find from the back
    std::string suffix = fname.substr(dotpos, fname.length() - 1);

    // Set content-type.
    SetContentType(suffix, &ret);

    // Set body
    ret.body = filecontent;
    // Set the protocol, response code and message in HttpResponse
    ret.protocol = "HTTP/1.1";
    ret.response_code = 200;
    ret.message = "OK";
    return ret;
  }

  // If you couldn't find the file, return an HTTP 404 error.
  ret.protocol = "HTTP/1.1";
  ret.response_code = 404;
  ret.message = "Not Found";
  ret.body = "<html><body>Couldn't find file \"";
  ret.body +=  EscapeHTML(fname);
  ret.body += "\"</body></html>";
  return ret;
}

HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices) {
  // The response we're building up.
  HttpResponse ret;

  // Your job here is to figure out how to present the user with
  // the same query interface as our solution_binaries/http333d server.
  // A couple of notes:
  //
  //  - no matter what, you need to present the 333gle logo and the
  //    search box/button
  //
  //  - if the user had previously typed in a search query, you also
  //    need to display the search results.
  //
  //  - you'll want to use the URLParser to parse the uri and extract
  //    search terms from a typed-in search query.  convert them
  //    to lower case.
  //
  //  - you'll want to create and use a hw3::QueryProcessor to process
  //    the query against the search indices
  //
  //  - in your generated search results, see if you can figure out
  //    how to hyperlink results to the file contents, like we did
  //    in our solution_binaries/http333d.

  // MISSING:
  // Add <html> <head> and <title>
  // Then add <body> and 333gle logo and search box
  ret.body = "<html><head><title>333gle</title></head>";
  ret.body += "<body><center style=\"font-size:500%;\">";
  ret.body += "<span style=\"position:relative;bottom:-0.33em;color:orange;\">";
  ret.body += "3</span>";
  ret.body += "<span style=\"color:red;\">3</span>";
  ret.body += "<span style=\"color:gold;\">3</span>";
  ret.body += "<span style=\"color:blue;\">g</span>";
  ret.body += "<span style=\"color:green;\">l</span>";
  ret.body += "<span style=\"color:red;\">e</span></center>";
  ret.body += "<p></p><div style=\"height:20px;\"></div><center>";
  ret.body += "<form action=\"/query\" method=\"get\">";
  ret.body += "<input type=\"text\" size=30 name=\"terms\" />";
  ret.body += "<input type=\"submit\" value=\"Search\" />";
  ret.body += "</form></center><p></p>";

  // Process the query and add elements to html
  // First use URLParser to parse the uri
  URLParser urlparser;
  urlparser.Parse(uri);

  // Find what terms map to, which means the query
  // and then tolower case.
  std::string query = urlparser.get_args()["terms"];
  boost::to_lower(query);

  // Split the query into words and use QueryProcessor to process it.
  std::vector<std::string> words;
  boost::trim(query);
  boost::split(words, query, boost::is_any_of(" "), boost::token_compress_on);

  hw3::QueryProcessor qp(*indices, true);
  std::vector<hw3::QueryProcessor::QueryResult> qr = qp.ProcessQuery(words);

  // Check query result and build corresponding result.
  if (query.empty()) {
    ret.body += "<p></p>";
  } else if (qr.empty()) {
    // Foramt should be "No results found for (query)"
    ret.body += "<p><br>No results found for <b>";
    ret.body += EscapeHTML(query);
    ret.body += "</b><p></p>";
  } else {
    // Format: (num_res) results found for (query)
    //              hyperlink [index]
    ret.body += "<p><br>";
    ret.body += std::to_string(qr.size());
    ret.body += " results found for <b>";
    ret.body += EscapeHTML(query);
    ret.body += "</b><p></p>";

    // Show all hyperlink that are matched
    ret.body += "<ul>";
    for (size_t i = 0; i < qr.size(); i++) {
      ret.body += "<li><a href =\"";
      if (qr[i].document_name.substr(0, 7) != "http://")
        ret.body += "/static/";
      ret.body += qr[i].document_name;
      ret.body += "\">";
      ret.body += EscapeHTML(qr[i].document_name);
      ret.body += "</a> [";
      ret.body += std::to_string(qr[i].rank);
      ret.body += "]<br>";
    }
    ret.body += "</ul>";
  }
  // Add close bracet </body> </html>
  ret.body += "</body></html>"; 

  // Set other HttpResponse data.
  ret.protocol = "HTTP/1.1";
  ret.response_code = 200;
  ret.message = "OK";

  return ret;
}

static void SetContentType(const std::string &suffix, HttpResponse *resp) {
  // Set content type according to the suffix.
  // text/
  if (suffix == ".html" || suffix == ".htm")
    resp->headers["Content-type"] = "text/html";
  else if (suffix == ".txt" || suffix == ".")
    resp->headers["Content-type"] = "text/plain";
  else if (suffix == ".xml")
    resp->headers["Content-type"] = "text/xml";
  else if (suffix == ".csv")
    resp->headers["Content-type"] = "text/csv";
  else if (suffix == ".css")
    resp->headers["Content-type"] = "text/css";
  else if (suffix == ".js")
    resp->headers["Content-type"] = "text/javascript";
  // image/
  else if (suffix == ".png")
    resp->headers["Content-type"] = "image/png";
  else if (suffix == ".jpg" || suffix == ".jpeg")
    resp->headers["Content-type"] = "image/jpeg";
  else if (suffix == ".gif")
    resp->headers["Content-type"] = "image/gif";
  else if (suffix == ".tiff")
    resp->headers["Content-type"] = "image/tiff";
  // application/
  else
    resp->headers["Content-type"] = "text/plain";
}

}  // namespace hw4
