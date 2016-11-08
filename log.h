#ifndef __LOG_H__
#define __LOG_H__


#include <string>
#include <memory>

using namespace std;


typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFORMATION
} LogType;


class ILog
{
public:
    virtual void setLogFile(const string &filepath) = 0;
    virtual void local(const string &message, const LogType log_type) = 0;
};


class Log: public ILog
{
private:
    string _logPath;
    using ILog::setLogFile;

    /**
     * Create log string for writing to file
     * @msg: logging message
     * @type: log message type
     *
     * returns full log string width datetime and type
     */
    string makeLogMsg(const string &msg, const LogType type) const;

public:
    explicit Log();

    /*
     * Set path for saving log data in local file
     */
    inline void setLogFile(const string &filepath) { _logPath = filepath; }

    /**
     * Saving log data in local file
     * @message: log message
     * @logType: message type
     *
     * throw: error if fail access to file
     */
    void local(const string &message, const LogType logType);
};


#endif
