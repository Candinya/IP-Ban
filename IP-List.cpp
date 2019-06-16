#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "ipdb.hpp"

#define MAX_IP_LENGTH 16
#define MAX_ADDR_LENGTH 28

bool hasArg(const int argc, const char * * argv, std::string targArg) {
	for (int i = 0; i < argc; i++) {
		std::string args(argv[i]);
		if (args == targArg) {
			return true;
		}
	}
	return false;
}

int main(const int argc, const char * * argv) {
	if (argc == 1) {
		std::cout << "参数: 日志文件路径 [-db (在数据库中查找)] [-wlm 白名单标记] / [-nwl 只输出非白名单IP]" << std::endl;
		return -1;
	}
	std::ifstream logFile(argv[1]);
	if (!logFile.is_open()) {
		std::cout << "日志文件打开失败" << std::endl;
		return -1;
	}
	std::vector<std::string> IP_List;
	while (!logFile.eof()) {
		std::string This_IP;
		logFile >> This_IP;
		logFile.ignore(65535, '\n');
		int i = IP_List.size() - 1;
		for (; i >= 0; i--) {
			if (This_IP == IP_List[i]) {
				break;
			}
		}
		if (i == -1 && This_IP.size() >= 7) {
			IP_List.push_back(This_IP);
		}
	}
	logFile.close();


	std::string * IP_AddrList = nullptr;
	if (hasArg(argc, argv, "-db") || hasArg(argc, argv, "-wlm") || hasArg(argc, argv, "-nwl")) {
		auto db = std::make_shared<ipdb::City>("ipdb");
		IP_AddrList = new std::string[IP_List.size()];
		for (int i = IP_List.size() - 1; i >= 0; i--) {
			IP_AddrList[i] = db->FindInfo(IP_List[i], "CN").str();
		}
	}

	bool * IP_WhiteList = nullptr;
	if (hasArg(argc, argv, "-wlm") || hasArg(argc, argv, "-nwl")) {
		IP_WhiteList = new bool[IP_List.size()];
		std::vector<std::string> addrWL;
		std::ifstream wlFile("whitelist.txt");
		while (!wlFile.eof()) {
			char addrTmp[MAX_ADDR_LENGTH];
			wlFile.getline(addrTmp, MAX_ADDR_LENGTH);
			for (int i = 0; i < MAX_ADDR_LENGTH; i++) {
				if (addrTmp[i] == '\r' || addrTmp[i] == '\n') {
					addrTmp[i] = '\0';
					break;
				}
			}
			if (addrTmp[0] != '\r' && addrTmp[0] != '\n' && addrTmp[0] != ' ') {
				addrWL.push_back(addrTmp);
			}
		}
		wlFile.close();
		for (int i = IP_List.size() - 1; i >= 0; i--) {
			IP_WhiteList[i] = false;
			for (int j = addrWL.size() - 1; j >= 0; j--) {
				if (IP_AddrList[i] == addrWL[j]) {
					IP_WhiteList[i] = true;
					break;
				}
			}
		}
	}

	for (int i = IP_List.size() - 1; i >= 0; i--) {
		if (hasArg(argc, argv, "-nwl")) {
			if (!IP_WhiteList[i]) {
				std::cout << IP_List[i] << std::endl;
			}
		} else {
			std::cout << IP_List[i];
			if (hasArg(argc, argv, "-db")) {
				for (int j = MAX_IP_LENGTH - IP_List[i].length(); j >= 0; j--) {
					std::cout << ' ';
				}
				std::cout << IP_AddrList[i];
			}
			if (hasArg(argc, argv, "-wlm") && IP_WhiteList[i]) {
				for (int j = MAX_ADDR_LENGTH - IP_AddrList[i].length(); j >= 0; j--) {
					std::cout << ' ';
				}
				std::cout << "★";
			}
			std::cout << std::endl;
		}
		
	}

	if (hasArg(argc, argv, "-db")) {
		delete[] IP_AddrList;
	}

	if (hasArg(argc, argv, "-wlm")) {
		delete[] IP_WhiteList;
	}

	return 0;
}

