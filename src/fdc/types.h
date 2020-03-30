#include <set>
#include <queue>
#include <string>

#ifndef __fd_cover_types_inc__
#define __fd_cover_types_inc__

/**
 * @brief A cross-platform library for calculating the covers of functional
 * dependencies.
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
