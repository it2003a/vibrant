/*ckwg +5
 * Copyright 2010 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef _VIDTK_LOGGER_MINI_LOGGER_H_
#define _VIDTK_LOGGER_MINI_LOGGER_H_

#include <logger/vidtk_logger.h>
#include <vcl_ostream.h>

#include <boost/thread/mutex.hpp>


namespace vidtk {
namespace logger_ns {

class vidtk_mini_logger_formatter;


// ----------------------------------------------------------------
/** Minimal logging class.
 *
 * This class represents a minimal logging class that supports the
 * vidtk_logger interface.  The output is just sent to a stream and
 * you have no way of redirecting the output.
 *
 */
class vidtk_logger_mini_logger
  : public vidtk_logger
{
public:
  vidtk_logger_mini_logger(const char * const realm);
  virtual ~vidtk_logger_mini_logger();

  // Check to see if level is enabled
  virtual bool is_fatal_enabled() const;
  virtual bool is_error_enabled() const;
  virtual bool is_warn_enabled() const;
  virtual bool is_info_enabled() const;
  virtual bool is_debug_enabled() const;
  virtual bool is_trace_enabled() const;

  virtual void set_level(log_level_t lvl);
  virtual log_level_t get_level() const;

  virtual void log_fatal (vcl_string const & msg);
  virtual void log_fatal (vcl_string const & msg,
                          ::vidtk::logger_ns::location_info const & location);

  virtual void log_error (vcl_string const & msg);
  virtual void log_error (vcl_string const & msg,
                          ::vidtk::logger_ns::location_info const & location);

  virtual void log_warn (vcl_string const & msg);
  virtual void log_warn (vcl_string const & msg,
                         ::vidtk::logger_ns::location_info const & location);

  virtual void log_info (vcl_string const & msg);
  virtual void log_info (vcl_string const & msg,
                         ::vidtk::logger_ns::location_info const & location);

  virtual void log_debug (vcl_string const & msg);
  virtual void log_debug (vcl_string const & msg,
                          ::vidtk::logger_ns::location_info const & location);

  virtual void log_trace (vcl_string const & msg);
  virtual void log_trace (vcl_string const & msg,
                          ::vidtk::logger_ns::location_info const & location);

  // -- extended interface --
  void register_formatter (vidtk_mini_logger_formatter * fmt);


protected:
  vcl_ostream& get_stream();

  virtual void log_message (log_level_t level, vcl_string const& msg);
  virtual void log_message (log_level_t level, vcl_string const& msg,
                            ::vidtk::logger_ns::location_info const & location);

  virtual void log_message (log_level_t level, vcl_string const& msg,
                            vidtk_mini_logger_formatter & formatter);

  virtual void log_message (log_level_t level, vcl_string const& msg,
                            ::vidtk::logger_ns::location_info const & location,
                            vidtk_mini_logger_formatter & formatter);


private:
  log_level_t m_logLevel;       // current logging level

  boost::mutex m_lock;          // synchronization lock

  vidtk_mini_logger_formatter * m_formatter;

}; // end class


} // end namespace
} // end namespace

#endif /* _VIDTK_LOGGER_MINI_LOGGER_H_ */
