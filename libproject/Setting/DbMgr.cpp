#include "stdafx.h"
#include "dbmgr.h"
#include "dblogicallayer.h"

DBMgr::DBMgr() {
    dirty_data_ = 0;
}

DBMgr::~DBMgr() {
}

int DBMgr::initialize_while_websites() {
    return 0;
}
int DBMgr::initialize_black_websites() {
    return 0;
}

int DBMgr::initialize_application_controlled() {
    return 0;
}

int DBMgr::initialize_su_logon() {
    return 0;
}

//============================
// auto clean
int DBMgr::auto_clean_websites_record(const int days) {
    auto_clean_website_list(days);
    auto_clean_wordsearched_list(days);
    return 0;
}

int DBMgr::auto_clean_searchword_record(const int days) {
    auto_clean_website_list(days);
    auto_clean_wordsearched_list(days);
    return 0;
}