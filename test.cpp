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

// 禁止 —— 污染命名空间
using namespace foo;


// 在 .cc 中使用别名缩短常用的命名空间
namespace baz = ::foo::bar::baz;


// 在 .h 中使用别名缩短常用的命名空间
namespace librarian {
namespace impl {  // 仅限内部使用
namespace sidetable = ::pipeline_diagnostics::sidetable;
}  // namespace impl

inline void my_inline_function() {
  // 限制在一个函数中的命名空间别名
  namespace baz = ::foo::bar::baz;
  ...
}
}  // namespace librarian
