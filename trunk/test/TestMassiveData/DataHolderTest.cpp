#include "stdafx.h"
#include "dataholderTest.h"
#include <DataHolder\AppList.h>
#include <DataHolder\WebsiteList.h>
#include <DataHolder\WordList.h>
#include <boost\test\test_tools.hpp>
using namespace boost::unit_test;

int DataHolderTest_ApplicationList() {
    const char * app1 = "aaabbbccdd";
    const char * app2 = "baabbbccdd";
    const char * app3 = "caabbbccdd";
    const char * app4 = "daabbbccdd";
    const char * app5 = "eaabbbccdd";
    const char * apps[] = {app1, app2, app3, app4};
    const int item_inserted = 4;

    ApplicationList app_list;
    app_list.add_item(app1);
    app_list.add_item(app2);
    app_list.add_item(app3);
    app_list.add_item(app4);

    // 插入相同的项，不真正被插入
    BOOST_CHECK(item_inserted == app_list.get_item_num());
    app_list.add_item(app4);
    BOOST_CHECK(item_inserted == app_list.get_item_num());

    BOOST_CHECK(true == app_list.check_path(app1));
    BOOST_CHECK(true == app_list.check_path(app2));
    BOOST_CHECK(true == app_list.check_path(app3));
    BOOST_CHECK(true == app_list.check_path(app4));
    

    // 枚举
    ApplicationList::FILEINFO fileinfo;
    int cnt = 0;
    std::string item, nextitem;
    BOOST_CHECK(0 == app_list.get_first_item(&item, &fileinfo));
    BOOST_CHECK(item == app1);

    cnt ++;
    while (1) {
        if (cnt == app_list.get_item_num() ) {
            BOOST_CHECK(0 != app_list.get_next_item(item, &nextitem, &fileinfo));
            break;
        } else {
            BOOST_CHECK(0 == app_list.get_next_item(item, &nextitem, &fileinfo));
            BOOST_CHECK(nextitem == apps[cnt++]);
            item = nextitem;
        }
    }

    // 测试删除
    BOOST_CHECK(0 == app_list.remote_item(app4));
    BOOST_CHECK(0 != app_list.remote_item(app5));

    BOOST_CHECK(item_inserted -1 == app_list.get_item_num());

    BOOST_CHECK(true == app_list.check_path(app1));
    BOOST_CHECK(true == app_list.check_path(app2));
    BOOST_CHECK(true == app_list.check_path(app3));
    BOOST_CHECK(false == app_list.check_path(app4));
    return 0;
}

int DataHolderTest_WebsitesList() {
    return 0;
}

int DataHolderTest_WordsList() {
    return 0;
}