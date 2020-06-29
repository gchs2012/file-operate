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


ReturnType ClassName::FunctionName(Type par_name1, Type par_name2) {
  DoSomething();
  ...
}


ReturnType ClassName::ReallyLongFunctionName(Type par_name1, Type par_name2,
                                             Type par_name3) {
  DoSomething();
  ...
}

ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
    Type par_name1,  // 4 space indent
    Type par_name2,
    Type par_name3) {
  DoSomething();  // 2 space indent
  ...
}
