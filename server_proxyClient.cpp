/*
 * server_proxyClient.cpp
 *
 *  Created on: 8 nov. 2016
 *      Author: kmoriell
 */

#include "server_proxyClient.h"

ProxyClient::ProxyClient(Socket &socket, Server &server) {

}

Object* ProxyClient::send() {

}

void ProxyClient::receive(std::string code) {
	if (!workspace)
		// TODO: error
		//sendError("");
		;
	workspace->receive(code);

}

void ProxyClient::loadWorkspace(std::string name) {
	std::string code = server.loadWorkspace(name);
	workspace = new Workspace(name);
	try {
	workspace->receive(code);
	} catch(const std::runtime_error &e) {
		delete workspace;
		sendError(e.what());
	}
}

std::vector<std::string> ProxyClient::availableWorkspace() {


}

void ProxyClient::newWorkspace(std::string name) {

}

void ProxyClient::closeWorkspace(std::string name) {

}

void ProxyClient::deleteWorkspace(std::string name) {

}

void ProxyClient::run() {
	while (!_interrupt) {
		try {
			int s = this->receive();
			if (s == 0) {
				finished = true;
				server.disconectedClient();
				break;
			}

		} catch (const std::runtime_error &e) {
			if (!_interrupt)
				throw e;
		}
	}
}

