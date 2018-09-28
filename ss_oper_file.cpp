/******************************************************************************

            版权所有 (C), 2017-2018, xxx Co.xxx, Ltd.

 ******************************************************************************
    文 件 名 : ss_oper_file.cpp
    版 本 号 : V1.0
    作    者 : zc
    生成日期 : 2018年9月28日
    功能描述 : 文件操作类接口实现
    修改历史 :
******************************************************************************/
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "ss_oper_file.h"

/*****************************************************************************
    函 数 名 : SsOperFile.SsOperFile
    功能描述 : 构造函数
    输入参数 : 无
    输出参数 : 无
    返 回 值 : 无
    作    者 : zc
    日    期 : 2018年9月28日
*****************************************************************************/
SsOperFile::SsOperFile(const char *pathname, int flags, mode_t mode)
    : m_fd(-1),
    m_error("") {

    if (pathname != NULL) {
        m_fd = open(pathname, flags, mode);
        if (m_fd < 0) {
            m_error.append("Open file ").append(pathname);
            m_error.append(" failed, err = ").append(strerror(errno));
        }
    } else {
        m_error = "File or directory is null";
    }
}

/*****************************************************************************
    函 数 名 : SsOperFile.~SsOperFile
    功能描述 : 析构函数
    输入参数 : 无
    输出参数 : 无
    返 回 值 : 无
    作    者 : zc
    日    期 : 2018年9月28日
*****************************************************************************/
SsOperFile::~SsOperFile() {
    if (m_fd >= 0) {
        close(m_fd);
        m_fd = -1;
    }
}

/*****************************************************************************
    函 数 名 : SsOperFile.is_open
    功能描述 : 判断是否打开文件
    输入参数 : 无
    输出参数 : 无
    返 回 值 : bool
    作    者 : zc
    日    期 : 2018年9月28日
*****************************************************************************/
bool SsOperFile::is_open() {
    return (m_fd >= 0) ? true : false;
}

/*****************************************************************************
    函 数 名 : SsOperFile.setFileLock
    功能描述 : 设置文件锁
    输入参数 : int type
    输出参数 : 无
    返 回 值 : bool
    作    者 : zc
    日    期 : 2018年9月28日
*****************************************************************************/
bool SsOperFile::setFileLock(int type) {
    struct flock lock;

    lock.l_whence = SEEK_SET;
    lock.l_type = type;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(m_fd, F_SETLKW, &lock) < 0) {
        if (type != F_UNLCK) {
            m_error = "lock(";
        } else {
            m_error = "unlock(";
        }
        m_error.append(std::to_string(type));
        m_error.append(") file failed, err = ").append(strerror(errno));
        return false;
    }

    return true;
}

/*****************************************************************************
    函 数 名 : SsOperFile.getFileLock
    功能描述 : 获取文件锁状态
    输入参数 : int type
    输出参数 : 无
    返 回 值 : int
    作    者 : zc
    日    期 : 2018年9月28日
*****************************************************************************/
int SsOperFile::getFileLock(int type) {
    struct flock lock;

    lock.l_whence = SEEK_SET;
    lock.l_type = type;
    lock.l_start = 0;
    lock.l_pid = -1;
    lock.l_len = 0;

    if (fcntl(m_fd, F_GETLK, &lock) < 0) {
        m_error.clear();
        m_error.append("get file lock failed, err = ");
        m_error.append(strerror(errno));
        return -1;
    }

    if ((type == F_WRLCK && lock.l_type == F_RDLCK) ||
        (type == F_RDLCK && lock.l_type == F_WRLCK)) {
        return 1;
    }

    return 0;
}

/*****************************************************************************
    函 数 名 : SsOperFile.getErrorInfo
    功能描述 : 获取文件操作错误信息
    输入参数 : 无
    输出参数 : 无
    返 回 值 : const char *
    作    者 : zc
    日    期 : 2018年9月28日
*****************************************************************************/
const char * SsOperFile::getErrorInfo() {
    return m_error.c_str();
}
