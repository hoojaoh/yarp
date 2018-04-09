/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_OS_IMPL_LOGGER_H
#define YARP_OS_IMPL_LOGGER_H

#include <yarp/conf/api.h>
#include <yarp/conf/system.h>
#include <yarp/os/ConstString.h>
#include <yarp/os/Log.h>
#include <yarp/os/impl/PlatformStdio.h>

#ifdef YARP_HAS_ACE
# include <ace/Log_Priority.h>
# include <ace/Log_Msg_Callback.h>
// In one of these files or their inclusions, there is a definition of "main"
// for WIN32
# ifdef main
#  undef main
# endif
#else
#  define LM_DEBUG      04
#  define LM_INFO      010
#  define LM_WARNING   040
#  define LM_ERROR    0200
#endif


namespace yarp {
namespace os {
namespace impl {

/**
 * This is a wrapper for message logging.
 * This is currently a sad mixture of the java yarp logging mechanism
 * and ACE.
 */
class YARP_OS_impl_API Logger : public yarp::os::Log
#ifdef YARP_HAS_ACE
                              , public ACE_Log_Msg_Callback
#endif
{
public:
    enum Level {
        MAJOR_DEBUG=LM_INFO,
        DEFAULT_WARN=LM_INFO
    };

    Logger(const char *prefix, Logger *parent = nullptr);
    Logger(const char *prefix, Logger& parent);

    static Logger& get();

#ifdef YARP_HAS_ACE
    virtual void log(ACE_Log_Record& log_record) override;
#endif

    void println(const ConstString& txt);
    void internal_debug(const ConstString& txt);
    void internal_info(const ConstString& txt);
    void internal_warning(const ConstString& txt);
    void internal_error(const ConstString& txt);
    void internal_fail(const ConstString& txt);
    void internal_debug(const char *txt);
    void internal_info(const char *txt);
    void internal_warning(const char *txt);
    void internal_error(const char *txt);
    void internal_fail(const char *txt);
    void assertion(bool cond);
    void setVerbosity(int verbose = 0);
    void setPrefix(const char *prefix);
    void setPid();
    long int getPid();
    bool shouldShowInfo();
    bool shouldShowError();
    bool shouldShowDebug();

private:
    void show(unsigned YARP_INT32 level, const ConstString& txt);

    ConstString prefix;
    Logger *parent;
    int verbose;
    unsigned YARP_INT32 low;
    long int pid;
    FILE *stream;
};

} // namespace impl
} // namespace os
} // namespace yarp


// compromise - use macros so that debugging can evaporate in optimized code.
// also, make a printf-style adaptor since c++ is a bit of a pain to
// build strings in.
#define YARP_ERROR(log, x) ((yarp::os::impl::Logger*)&(log))->internal_error(x)
#define YARP_WARN(log, x)  ((yarp::os::impl::Logger*)&(log))->internal_warning(x)
#define YARP_INFO(log, x)  ((yarp::os::impl::Logger*)&(log))->internal_info(x)
#ifndef NDEBUG
#  define YARP_DEBUG(log, x) ((yarp::os::impl::Logger*)&(log))->internal_debug(x)
#else
#  define YARP_DEBUG(log, x) YARP_UNUSED(log)
#endif
#define YARP_FAIL(log, x)  ((yarp::os::impl::Logger*)&(log))->internal_fail(x)

#define YARP_LONGEST_MESSAGE 1000
#define YARP_SPRINTF0(log, mode, msg)  { char _yarp_buf[YARP_LONGEST_MESSAGE]; snprintf(&(_yarp_buf[0]), YARP_LONGEST_MESSAGE, msg); (log).internal_ ## mode(&(_yarp_buf[0])); }
#define YARP_SPRINTF1(log, mode, msg, a)  { char _yarp_buf[YARP_LONGEST_MESSAGE]; snprintf(&(_yarp_buf[0]), YARP_LONGEST_MESSAGE, msg, a); (log).internal_ ## mode(&(_yarp_buf[0])); }
#define YARP_SPRINTF2(log, mode, msg, a, b)  { char _yarp_buf[YARP_LONGEST_MESSAGE]; snprintf(&(_yarp_buf[0]), YARP_LONGEST_MESSAGE, msg, a, b); (log).internal_ ## mode(&(_yarp_buf[0])); }
#define YARP_SPRINTF3(log, mode, msg, a, b, c)  { char _yarp_buf[YARP_LONGEST_MESSAGE]; snprintf(&(_yarp_buf[0]), YARP_LONGEST_MESSAGE, msg, a, b, c); (log).internal_ ## mode(&(_yarp_buf[0])); }
#define YARP_SPRINTF4(log, mode, msg, a, b, c, d)  { char _yarp_buf[YARP_LONGEST_MESSAGE]; snprintf(&(_yarp_buf[0]), YARP_LONGEST_MESSAGE, msg, a, b, c, d); (log).internal_ ## mode(&(_yarp_buf[0])); }
#define YARP_SPRINTF5(log, mode, msg, a, b, c, d, e)  { char _yarp_buf[YARP_LONGEST_MESSAGE]; snprintf(&(_yarp_buf[0]), YARP_LONGEST_MESSAGE, msg, a, b, c, d, e); (log).internal_ ## mode(&(_yarp_buf[0])); }



#endif // YARP_OS_IMPL_LOGGER_H
