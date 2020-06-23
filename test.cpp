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



int i;
i = f(); // 坏——初始化和声明分离

int j = g(); // 好——初始化时声明

vector<int> v;
v.push_back(1); // 用花括号初始化更好
v.push_back(2);

vector<int> v = {1, 2}; // 好——v 一开始就初始化
