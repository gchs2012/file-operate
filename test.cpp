#include <iostream>
#include <boost/scoped_ptr.hpp>

#include "ss_oper_file.h"

int main(int argc, char const *argv[])
{
    SsOperFile *ptr = new SsOperFile("test.conf",
                                     O_WRONLY|O_CREAT,
                                     0666);
    boost::scoped_ptr<SsOperFile> s_ptr(ptr);
    if (s_ptr == nullptr) {
        std::cout << "new SsOperFile failed" << std::endl;
        return -1;
    }

    if (s_ptr->is_open() != true) {
        std::cout << s_ptr->getErrInfo() << std::endl;
        return -1;
    }

    if (s_ptr->getFileLock(F_WRLCK) == 0) {
        if (s_ptr->setFileLock(F_WRLCK)) {
            std::cout << "write locked" << std::endl;
            s_ptr->setFileLock(F_UNLCK);
        }
    }

    return 0;
}



std::string table_name;  // 好 - 用下划线.
std::string tablename;   // 好 - 全小写.

std::string tableName;  // 差 - 混合大小写


class TableInfo {
  ...
 private:
  std::string table_name_;  // 好 - 后加下划线.
  std::string tablename_;   // 好.
  static Pool<TableInfo>* pool_;  // 好.
};


struct UrlTableProperties {
  std::string name;
  int num_entries;
  static Pool<UrlTableProperties>* pool;
};
