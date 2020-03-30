/**
 * @file fds/types.h
 * @brief Basic typedefs for fdc.
 * @author: Guangrui Wang
 * @email: aguang.xyz@gmail.com
 * @version: 1.0.0
 * @date 2020-03-30
 */

#include <set>
#include <queue>
#include <string>

#ifndef __fd_cover_types_inc__
#define __fd_cover_types_inc__

/**
 * @brief Functional Dependency Cover Library.
 */
namespace fdc {

  /**
   * @brief Attribute.
   */
  typedef std::string attr;

  /**
   * @brief A set of attributes.
   */
  typedef std::set<attr> attrs;

  /**
   * @brief Functional dependency.
   */
  typedef std::pair<attrs, attrs> fd;

  /**
   * @brief A set of functional dependencies.
   */
  typedef std::set<fd> fds;
}

#endif
