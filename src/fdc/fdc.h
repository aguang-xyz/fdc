#include <iostream>
#include <queue>
#include <set>
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
   * @brief Convert a json string `input` into a set of attributes `U` and a
   * set of functional dependencies `F`.
   *
   * The json string `input` is expected to be under the structure below:
   *
   * {
   *   "R": Integer,
   *   fds": [
   *     {
   *       "lhs": [ Integer ],
   *       "rhs": [ Integer ]
   *     }
   *   ]
   * }
   *
   * @param input: A json string.
   * @param U: A set of attributes for output.
   * @param F: A set of functional dependencies for output.
   */
  void from_json(const std::string input, attrs &U, fds &F);
 
  /**
   * @brief Convert a input stream `input` into a set of attributes `U` and a
   * set of functional dependencies `F`.
   *
   * The input stream `input` is expected to be under the structure below:
   *
   * {
   *   "R": Integer,
   *   fds": [
   *     {
   *       "lhs": [ Integer ],
   *       "rhs": [ Integer ]
   *     }
   *   ]
   * }
   *
   * @param input: A input stream.
   * @param U: A set of attributes for output.
   * @param F: A set of functional dependencies for output.
   */
  void from_json(std::istream &input, attrs &U, fds &F);

  /**
   * @brief Convert given set of attributes `U` and given set of functional
   * dependencies `F` to json string and write it into output.
   *
   * The output stream `output` is expected to be written under the structure
   * below:
   *
   * {
   *   "R": Integer,
   *   fds": [
   *     {
   *       "lhs": [ Integer ],
   *       "rhs": [ Integer ]
   *     }
   *   ]
   * }
   *
   * @param output: An output stream.
   * @param U: A set of attributes.
   * @param F: A set of functional dependencies.
   */
  void to_json(std::ostream &output, const attrs &U, const fds &F);

  /**
   * @brief Convert an attribute `x` to a string.
   *
   * @param x: a given attribute
   */
  std::string to_str(const attr &x);

  /**
   * @brief Convert a set of attributes `X` to a string.
   *
   * @param X: a given set of attributes.
   */
  std::string to_str(const attrs &X);

  /**
   * @brief Convert a set of functional depdency `f` to a string.
   *
   * @param f: a given functional dependency.
   */
  std::string to_str(const fd &f);

  /**
   * @brief Convert a set of functional dependencies `F` to a string.
   *
   * @param F: a given set of functional dependencies.
   */
  std::string to_str(const fds &F);

  /**
   * @brief Get all attributes of a given functional dependency set `F`.
   *
   * @param F: a given set of functional dependencies.
   */
  attrs attrs_of(const fds &F);


  /**
   * @brief Get all subsets of a given set attributes `X`.
   *
   * @param X: A set of attributes.
   */
  std::set<attrs> subsets_of(const attrs &X);

  /**
   * @brief Get all subsets of a given set of functional dependencies `F`.
   *
   * @param F: A set of functional dependencies.
   */
  std::set<fds> subsets_of(const fds &F);

  /**
   * @brief Get the closure of a given set of functional depdencies `F`. It is
   * an implementation of Armstrong's Axioms.
   *
   * @param F: A set of functional dependencies.
   */
  fds closure_of(const fds &F);

  /**
   * @brief Get the closure of a given set of functional depdencies `F` under a
   * given set of attributes, universe `U`. It is an implementation of
   * Armstrong's Axioms.
   *
   * @param U: Universal set of attributes.
   * @param F: A set of functional dependencies.
   */
  fds closure_of(const attrs &U, const fds &F);

  /**
   * @brief Check if two given sets of functional dependencies are equivalent.
   *
   * @param F: A set of functional dependencies.
   * @param G: A set of functional dependencies.
   */
  bool equal(const fds &F, const fds &G);

  /**
   * @brief Check if a given set of functional dependencies `F` is a cover of
   * another given set of functional dependencies `G`.
   *
   * @param F: A set of functional dependencies.
   * @param G: A set of functional dependencies.
   */
  bool is_cover_of(const fds &F, const fds &G);

  /**
   * @brief Check if two sets of attributes `X` and `Y` are equivalent under
   * a given set of functional dependencies `F`.
   *
   * @param X: A set of attributes.
   * @param Y: A set of attributes.
   * @param F: A set of functional dependencies.
   */
  bool equal(const attrs &X, const attrs &Y, const fds &F);

  /**
   * @brief Check if a given set of functional dependencies is canonical.
   *
   * @param F: A set of functional dependencies.
   */
  bool is_canonical(const fds &F);



  /*! \brief Basic algebras of sets implemented in `FDC`.
   *
   * This module contains the basic algebras of sets implemented in `FDC`.
   *
   * @defgroup set_algebra
   *
   * @{
   */

  /*! \brief Atributes minus.
   *
   * Given two set of attributes \f$ X \f$, \f$ Y \f$, calculate \f$ X - Y \f$.
   *
   * @param X: A set of attributes.
   * @param Y: A set of attributes.
   */
  attrs minus(const attrs &X, const attrs &Y);
 
  /*! \brief Functional dependencies minus.
   *
   * Given two set of functional dependencies \f$ X \f$, \f$ Y \f$,
   * calculate \f$ X - Y \f$.
   *
   * @param X: A set of functional dependencies.
   * @param Y: A set of attributes dependencies.
   */
  fds minus(const fds &X, const fds &Y);

  /*! \brief Attributes subset or equal determination.
   *
   * Given two set of attributes \f$ X\f$, \f$ Y \f$, determine if
   * \f$ X \subseteq Y \f$.
   *
   * @param X: A set of attributes.
   * @param Y: A set of attributes.
   */
  bool is_subset_eq(const attrs &X, const attrs &Y);

  /*! \brief Functional dependencies subset or equal determination.
   *
   * Given two set of functioanl dependencies \f$ X\f$, \f$ Y \f$, determine if
   * \f$ X \subseteq Y \f$.
   *
   * @param X: A set of functional dependencies.
   * @param Y: A set of functional dependencies.
   */
  bool is_subset_eq(const fds &X, const fds &Y);

  /*! \brief Attributes set union.
   * 
   * Given two sets of attributes `X`, `Y`, calculate \f$ X \cup Y \f$.
   *
   * @param X: A set of attributes.
   * @param Y: A set of attributes.
   */
  attrs union_of(const attrs &X, const attrs &Y);

  /** @} */



  /*! \brief The algorithms implemented in `FDC`.
   *
   * This module contains the algorithms implemented in `FDC`.
   *
   * \dot
   *   digraph algorithsm {
   *
   *     node[shape=rect];
   *
   *     depend[label = "attrs depend(const fds &F, const attrs &X)"]
   *     is_membership[label = "bool is_membership(const fds &F, const fd &f)"]
   *     is_redundant[label = "bool is_redundant(const fds &F)"]
   *     non_redundant[label = "fds non_redundant(const fds &F)"]
   *     is_direct[label = "bool is_direct(const fds &F, const fd &f)"]
   *     minimum[label = "fds minimum(const fds &F)"]
   *
   *     is_membership -> depend
   *     is_redundant -> is_membership
   *     non_redundant -> is_membership
   *     is_direct -> non_redundant
   *     minimum -> non_redundant
   *   }
   * \enddot
   *
   * @defgroup algorithms
   *
   * @{
   */

  /*! \brief Dependent calculation.
   *
   * Given a set of functional dependencies \f$ F \f$ and a set of attributes
   * \f$ X \f$, calculate the set of attributes \f$ \{ y \mid X \to y \in F^+ \} \f$.
   *
   * Time complexity: \f$ O(|F|) \f$
   *
   * See also: [Beeri and Bernstein (1979, p. 46)](https://dl.acm.org/doi/10.1145/320064.320066)
   *
   * @param F: A set of functional dependencies.
   * @param X: A set of attributes.
   */
  attrs depend(const fds &F, const attrs &X);

  /*! \brief Membership determination.
   *
   * Given a set of functional dependencies \f$ F \f$ and a functional
   * dependency \f$ f \f$ , determine if \f$ f \in F^{+} \f$.
   *
   * Time complexity: \f$ O(|F|) \f$
   *
   * See also: [Beeri and Bernstein (1979, p. 46)](https://dl.acm.org/doi/10.1145/320064.320066)
   *
   * @param F: A set of functional dependencies.
   * @param f: A functional dependency.
   */
  bool is_membership(const fds &F, const fd &f);

  /*! \brief Redundant determination.
   *
   * Check if a set of functional dependencies \f$ F \f$ is redundant.
   *
   * If there is a \f$ \ f \in F \f$, where \f$ (F - \{f\})^+ = F^+ \f$, then
   * we say \f$ F \f$ is redundant.
   *
   * Time complexity: \f$ O(|F|^2) \f$.
   *
   * See also: [Beeri and Bernstein (1979, p. 48)](https://dl.acm.org/doi/10.1145/320064.320066)
   *
   * @param F: A set of functional dependencies.
   */
  bool is_redundant(const fds &F);

  /*! \brief Redundant cover calculation.
   *
   * Given a set of functional dependencies \f$ F \f$, calculate a non-redundant
   * cover \f$ G \f$ of \f$ F \f$, where:
   *
   *   * \f$ G^+ = F^+ \f$
   *   * \f$ \forall H \subset G: H^{+} \neq F^+ \f$
   *
   * Time complexity: \f$ O(|F|^2) \f$.
   *
   * See also: [Beeri and Bernstein (1979, p. 48)](https://dl.acm.org/doi/10.1145/320064.320066)
   *
   * @param F: A set of functional dependencies.
   */
  fds non_redundant(const fds &F);

  /*! \brief Direct determination.
   *
   * Given a set of functional dependencies \f$ F \f$ and a functional
   * dependency \f$ f:X \to Y \f$, determine if \f$ X \f$ directly determines
   * \f$ Y \f$.
   *
   * Time complexity: \f$ O(|F|^2) \f$.
   *
   * See also: [Maier(1979, p. 335)](https://dl.acm.org/doi/10.1145/800135.804425)
   *
   * @param F: A set of functional dependencies.
   * @param f: A functional dependency.
   */
  bool is_direct(const fds &F, const fd &f);

  /*! \brief Minimum cover calculation.
   *
   * Given a set of functional dependencies \f$ F \f$, calculate a minimum
   * cover \f$ G \f$, where:
   * 
   *   * \f$ G^+ = F^+ \f$.
   *   * \f$ \forall H^+ = F^+, |H| \geq |G| \f$.
   *
   * Time complexity: \f$ O(|F|^2) \f$.
   *
   * See also: [Maier(1979, p. 335)](https://dl.acm.org/doi/10.1145/800135.804425)
   *
   * @param F: A set of functional dependencies.
   */
  fds minimum(const fds &F);

  /** @} */
}
#endif
