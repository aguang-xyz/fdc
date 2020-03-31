#include <set>
#include <queue>
#include <string>

#ifndef __fdc_inc__
#define __fdc_inc__

#define FDC_VERSION_MAJOR @FDC_VERSION_MAJOR@
#define FDC_VERSION_MINOR @FDC_VERSION_MINOR@
#define FDC_VERSION_PATCH @FDC_VERSION_PATCH@

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
   * @brief Get all subsets of a given set of functional dependencies `F`.
   *
   * @param F: A set of functional dependencies.
   *
   * @return A set of sets of functional dependencies.
   */
  std::set<fds> subsets_of(fds F);

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
   * @brief Get the closure of a given set of functional depdencies `F`. It is
   * an implementation of Armstrong's Axioms.
   *
   * @param F: A set of functional dependencies.
   *
   * @return A set of functional depdencies.
   */
  fds closure_of(fds F);

  /**
   * @brief Get the closure of a given set of functional depdencies `F` under a
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


  /**
   * @brief Check if two sets of attributes `X` and `Y` are equivalent under
   * a given set of functional dependencies `F`.
   *
   * @param X: A set of attributes.
   * @param Y: A set of attributes.
   * @param F: A set of functional dependencies.
   *
   * @return bool
   */
  bool equal(attrs X, attrs Y, fds F);

  /**
   * @brief Check if a given set of functional dependencies is non-redundant.
   *
   * @param F: A set of functional dependnecies.
   *
   * @return bool
   */
  bool is_non_redundant(fds F);

  /**
   * @brief Check if a given set of functional dependencies is canonical.
   *
   * @param F: A set of functional dependencies.
   *
   * @return bool
   */
  bool is_canonical(fds F);
}
#endif
