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


x = *p;
p = &x;
x = r.y;
x = r->y;

// 好, 空格前置.
char *c;
const string &str;

// 好, 空格后置.
char* c;
const string& str;
int x, *y;  // 不允许 - 在多重声明中不能使用 & 或 *
char * c;  // 差 - * 两边都有空格
const string & str;  // 差 - & 两边都有空格.
