#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

void handleClients();

void initHttpServer(const char* ssid, const char* password);

void defineRoots();

void handleIndex();

void handleCSS();

#endif