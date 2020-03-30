#include "types.h"

#ifndef __fd_cover_utils_inc__
#define __fd_cover_utils_inc__

namespace fdc {

  /**
   * @brief Convert a attribute `x` to a string.
   *
   * @param x: a given attribute
   *
   * @return string
   */
  std::string to_str(attr x);

  /**
   * @brief Convert a set of attributes `X` to a string.
   *
   * @param X: a given set of attributes.
   *
   * @return string
   */
  std::string to_str(attrs X);

  /**
   * @brief Convert a set of functional depdency `f` to a string.
   *
   * @param f: a given functional dependency.
   *
   * @return string
   */
  std::string to_str(fd f);

  /**
   * @brief Convert a set of functional dependencies `F` to a string.
   *
   * @param F: a given set of functional dependencies.
   *
   * @return string
   */
  std::string to_str(fds F);

  /**
   * @brief Get all attributes of a given functional dependency set `F`.
   *
   * @param F: a given set of functional dependencies.
   *
   * @return A set of attributes.
   */
  attrs attrs_of(fds F);

  /**
   * @brief Get the union set of two sets of attributes `X`, `Y`.
   *
   * @param X: A set of attributes.
   * @param Y: A set of attributes.
   *
   * @return The union set of attibutes.
   */
  attrs union_of(attrs X, attrs Y);

  /**
   * @brief Get all subsets of a given set attributes `X`.
   *
   * @param X: A set of attributes.
   *
   * @return A set of sets of attributes.
   */
  std::set<attrs> subsets_of(attrs X);

  /**
   * @brief Check if given set of attributes `X` is a subset of given set of
   * attributes `Y`.
   *
   * @param X: A set of atributes.
   * @param Y: A set of attributes.
   *
   * @return bool
   */
  bool is_subset_of(attrs X, attrs Y);

  /**
   * @brief Get the closure of a given set of functional depdencies `F`under a
   * given set of attributes, universe `U`. It is an implementation of
   * Armstrong's Axioms.
   *
   * @param U: Universal set of attributes.
   * @param F: A set of functional dependencies.
   *
   * @return A set of functional depdencies.
   */
  fds closure_of(attrs U, fds F);

  /**
   * @brief Check if two given sets of functional dependencies are equivalent.
   *
   * @param F: A set of functional dependencies.
   * @param G: A set of functional dependencies.
   *
   * @return bool
   */
  bool equal(fds F, fds G);

  /**
   * @brief Check if a given set of functional dependencies `F` is a cover of
   * another given set of functional dependencies `G`.
   *
   * @param F: A set of functional dependencies.
   * @param G: A set of functional dependencies.
   *
   * @return bool
   */
  bool is_cover_of(fds F, fds G);
}

#endif
