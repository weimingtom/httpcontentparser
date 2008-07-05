#include "precomp.h"
#include ".\fileloglistener.h"
#include ".\loglayout.h" 
 
#include <stdlib.h>
#include <stdio.h>

namespace LogSystem {
 
FileLogListener::FileLogListener(const std::string &filename, const std::string &name) : 
LogListener(name), filename_(filename) {
	file_.open(filename.c_str(), std::ios::out | std::ios::app);
}

FileLogListener::~FileLogListener(void) {
}
 
void FileLogListener::UpdateMessage(const char *msg, const int len) {
	file_.write(msg, len);
}

};