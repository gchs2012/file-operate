/******************************************************************************

            版权所有 (C), 2017-2018, xxx Co.xxx, Ltd.

 ******************************************************************************
    文 件 名 : ss_oper_file.h
    版 本 号 : V1.0
    作    者 : zc
    生成日期 : 2018年9月28日
    功能描述 : 文件操作类
    修改历史 :
******************************************************************************/
#ifndef _SS_OPER_FILE_H_
#define _SS_OPER_FILE_H_

#include <string>

/* 文件操作类 */
class SsOperFile {
public:
    SsOperFile(const char *pathname, int flags, mode_t mode);
    ~SsOperFile();
    bool is_open();
    bool setFileLock(int type);
    int getFileLock(int type);
    const char * getErrorInfo();

private:
    int m_fd;
    std::string m_error;
};

#endif
