#include <iostream>
#include <vector>

#ifndef __fdc_inc__
#define __fdc_inc__

#define FDC_VERSION_MAJOR @FDC_VERSION_MAJOR @
#define FDC_VERSION_MINOR @FDC_VERSION_MINOR @
#define FDC_VERSION_PATCH @FDC_VERSION_PATCH @

/**
 * @brief A cross-platform library for calculating the covers of functional
 * dependencies.
 */
namespace fdc {

/*! \brief Attribute. */
typedef int attr;

/*! \brief A set of attributes. */
typedef std::vector<attr> attrs;

/*! \brief Functional dependency. */
typedef std::pair<attrs, attrs> fd;

/*! \brief A set of functional dependencies. */
typedef std::vector<fd> fds;

/*! \brief A boolean expressions. */
typedef std::vector<char> bool_expr;

/*! \brief A collection of boolean expressions. */
typedef std::vector<bool_expr> bool_exprs;

/*! \brief Input/output functions implemented in `FDC`.
 *
 * This module contains the input and output functions implemented in `FDC`.
 *
 * @defgroup IO
 *
 * @{
 */

/*! \brief Convert an attribute `x` to a string.
 *
 * @param x: a given attribute
 */
std::string to_str(const attr &x);

/*! \brief Convert a set of attributes `X` to a string.
 *
 * @param X: a given set of attributes.
 */
std::string to_str(const attrs &X);

/*! \brief Convert a set of functional depdency `f` to a string.
 *
 * @param f: a given functional dependency.
 */
std::string to_str(const fd &f);

/*! \brief Convert a set of functional dependencies `F` to a string.
 *
 * @param F: a given set of functional dependencies.
 */

std::string to_str(const fds &F);

/*! \brief Convert a json string `input` into a set of functional
 * dependencies `F`.
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
 * @param N: The total number of attributes for output.
 * @param F: A set of functional dependencies for output.
 */
void from_json(const std::string input, int &N, fds &F);

/*! \brief Convert a input stream `input` into a set of functional
 * dependencies `F`.
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
 * @param N: The total number of attributes for output.
 * @param F: A set of functional dependencies for output.
 */
void from_json(std::istream &input, int &N, fds &F);

/*! \brief Convert a set of functional dependencies `F` to json string and
 * write it into output.
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
 * @param N: The total number of attributes for output.
 * @param F: A set of functional dependencies.
 */
void to_json(std::ostream &output, const int &N, const fds &F);

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
 *     depend[label = "Depend"]
 *     is_membership[label = "Membership"]
 *     equal_attrs[label = "Attributes Equivalence"]
 *     equal_fds[label = "Functional Dependencies Equivalence"]
 *     is_redundant[label = "Redundant Determination"]
 *     non_redundant[label = "Redundant Cover"]
 *     is_direct[label = "Direct Determination"]
 *     minimum[label = "Minimum Cover"]
 *     l_minimum[label = "L-Minimum Cover"]
 *     lr_minimum[label = "LR-Minimum Cover"]
 *     mini[label = "Mini Cover"]
 *
 *     is_membership -> depend
 *     equal_attrs -> is_membership
 *     equal_fds -> is_membership
 *     is_redundant -> is_membership
 *     non_redundant -> is_membership
 *     is_direct -> non_redundant
 *     minimum -> non_redundant
 *     l_minimum -> minimum
 *     lr_minimum -> l_minimum
 *     optimal -> mini
 *   }
 * \enddot
 *
 * Brief relations between different kinds of covers:
 *
 * \dot
 *   digraph covers {
 *
 *     rankdir=RL;
 *     node[shape=rect];
 *
 *     canonical[label = "Canonical"]
 *     non_redundant[label = "Non-Redundant"]
 *     minimum[label = "Minimum"]
 *     l_minimum[label = "L-Minimum"]
 *     lr_minimum[label = "LR-Minimum"]
 *     optical[label = "Optical"]
 *     mini[label = "Mini"]
 *
 *     canonical -> non_redundant
 *     minimum -> non_redundant
 *     mini -> canonical
 *     l_minimum -> minimum
 *     lr_minimum -> l_minimum
 *     optical -> lr_minimum
 *     optical -> mini
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
 * \f$ X \f$, calculate the set of attributes \f$ \{ y \mid X \to y \in F^+ \}
 * \f$.
 *
 * Time complexity: \f$ O(|F|) \f$
 *
 * See also: Algorithm 2. A linear-time membership algorithm in
 *   [Beeri and Bernstein (1979, p.
 * 46)](https://dl.acm.org/doi/10.1145/320064.320066)
 *
 * @param N: The total number of attributes.
 * @param F: A set of functional dependencies.
 * @param X: A set of attributes.
 * @param D: The output of the depend result.
 */
void depend(const int N, const fds &F, const std::vector<int> X, bool D[]);

/*! \brief Membership determination.
 *
 * Given a set of functional dependencies \f$ F \f$ and a functional
 * dependency \f$ f \f$ , determine if \f$ f \in F^{+} \f$.
 *
 * Time complexity: \f$ O(|F|) \f$
 *
 * See also: Algorithm 2. A linear-time membership algorithm in
 *   [Beeri and Bernstein (1979, p.
 * 46)](https://dl.acm.org/doi/10.1145/320064.320066)
 *
 * @param N: The total number of attributes.
 * @param F: A set of functional dependencies.
 * @param f: A functional dependency.
 */
bool is_membership(const int N, const fds &F, const fd &f);

/*! \brief Sets of attributes equivalence determination.
 *
 * Given two sets of attributes \f$ X \f$ and \f$ Y \f$ and a set of
 * functional dependencies \f$ F \f$.
 *
 * Determine if:
 *
 *   * \f$ X \to Y \in F^+ \f$
 *   * \f$ Y \to X \in F^+ \f$
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 * @param X: A set of attributes.
 * @param Y: A set of attributes.
 */
bool equal(const int N, const fds &F, const attrs &X, const attrs &Y);

/*! \brief Functional dependencies equivalence determination.
 *
 * Given two sets of functional dependencies.
 * Determine if \f$ F^+ = G^+ \f$.
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 * @param G: A set of functional dependencies.
 */
bool equal(const int N, const fds &F, const fds &G);

/*! \brief Redundant determination.
 *
 * Check if a set of functional dependencies \f$ F \f$ is redundant.
 *
 * If there is a \f$ \ f \in F \f$, where \f$ (F - \{f\})^+ = F^+ \f$, then
 * we say \f$ F \f$ is redundant.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: 5.2 Redundancy Tests in
 *   [Beeri and Bernstein (1979, p.
 * 47)](https://dl.acm.org/doi/10.1145/320064.320066)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
bool is_redundant(const int N, const fds &F);

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
 * See also: 5.2 Redundancy Tests in
 *   [Beeri and Bernstein (1979, p.
 * 47)](https://dl.acm.org/doi/10.1145/320064.320066)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
fds non_redundant(const int N, const fds &F);

/*! \brief Canonical determination.
 *
 * Given a set of functional dependencies \f$ F \f$, determine if \f$ F \f$
 * is canonical.
 *
 * The definition of canonical:
 *
 *   * \f$ F \f$ is non-redundant.
 *   * For every \f$ X \to Y \in F \f$, \f$ |Y| = 1\f$ and there is no such
 *     a \f$ X^{'} \subset X \f$ where \f$ X^{'} \to Y \in F \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: 5.2 Redundancy Tests in
 *   [Beeri and Bernstein (1979, p.
 * 47)](https://dl.acm.org/doi/10.1145/320064.320066)
 *
 * @param N: The number of attributes.
 * @param F: A set of cuntional dependencies.
 */
bool is_canonical(const int N, const fds &F);

/*! \brief Canonical calculation.
 *
 * Given a set of functional dependencies \f$ F \f$, calculate
 * \f$ G^+ = F^+ \f$ where
 *
 *   * \f$ G \f$ is non-redundant.
 *   * For every \f$ X \to Y \in G \f$, \f$ |Y| = 1 \f$ and there is no such
 *     a \f$ X^{'} \subset X \f$ where \f$ X^{'} \to Y \in G \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: 5.2 Redundancy Tests in
 *   [Beeri and Bernstein (1979, p.
 * 47)](https://dl.acm.org/doi/10.1145/320064.320066)
 *
 * @param N: The number of attributes.
 * @param F: A set of cuntional dependencies.
 */
fds canonical(const int N, const fds &F);

/*! \brief Direct determination.
 *
 * Given a set of functional dependencies \f$ F \f$ and a functional
 * dependency \f$ f:X \to Y \f$, determine if \f$ X \f$ directly determines
 * \f$ Y \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: Direct determination in
 *   [Maier(1979, p. 335)](https://dl.acm.org/doi/10.1145/800135.804425)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 * @param f: A functional dependency.
 */
bool is_direct(const int N, const fds &F, const fd &f);

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
 * See also: Theorem 3. in
 *   [Maier(1979, p. 335)](https://dl.acm.org/doi/10.1145/800135.804425)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
fds minimum(const int N, const fds &F);

/*! \brief Minimum determination.
 *
 * Given a set of functional dependencies \f$ F \f$, determine if:
 *
 *   * \f$ \forall G^+ = F^+, |G| \geq |F| \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: The definition of minimum in
 *   [Maier(1979, p. 331)](https://dl.acm.org/doi/10.1145/800135.804425)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
bool is_minimum(const int N, const fds &F);

/*! \brief L-minimum determination.
 *
 * Given a set of functional dependencies \f$ F \f$, determine if:
 *
 *   * \f$ \forall G^+ = F^+, |G| \geq |F| \f$.
 *   * For every \f$ X \to Y \in F \f$, there is no such
 *     a \f$ X^{'} \subset X \f$ where \f$ X^{'} \to Y \in F \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: The definition of L-minimum in
 *   [Maier(1979, p. 331)](https://dl.acm.org/doi/10.1145/800135.804425)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
bool is_lminimum(const int N, const fds &F);

/*! \brief L-minimum calculation.
 *
 * Given a set of functional dependencies \f$ F \f$, calculate \f$ G \f$
 * where:
 *
 *   * \f$ G^+ = F^+ \f$
 *   * \f$ \forall H^+ = G^+, |H| \geq |G| \f$.
 *   * For every \f$ X \to Y \in G \f$, there is no such
 *     a \f$ X^{'} \subset X \f$ where \f$ X^{'} \to Y \in G \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: Corollary 2. in
 *   [Maier(1979, p. 335)](https://dl.acm.org/doi/10.1145/800135.804425)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
fds lminimum(const int N, const fds &F);

/*! \brief LR-minimum determination.
 *
 * Given a set of functional dependencies \f$ F \f$, determine if:
 *
 *   * \f$ \forall G^+ = F^+, |G| \geq |F| \f$.
 *   * For every \f$ X \to Y \in F \f$, there is no such
 *     a \f$ X^{'} \subset X \f$ where \f$ X^{'} \to Y \in F \f$.
 *   * For every \f$ X \to Y \in F \f$, there is no such
 *     a \f$ Y^{'} \subset Y \f$ where
 *     \f$ (F - \{X \to Y\} + \{X \to Y^{'}\})^+ = F^+ \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: The definition of LR-minimum in
 *   [Maier(1979, p. 331)](https://dl.acm.org/doi/10.1145/800135.804425)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
bool is_lrminimum(const int N, const fds &F);

/*! \brief LR-minimum calculation.
 *
 * Given a set of functional dependencies \f$ F \f$, calculate \f$ G \f$
 * where:
 *
 *   * \f$ G^+ = F^+ \f$
 *   * \f$ \forall H^+ = F^+, |H| \geq |G| \f$.
 *   * For every \f$ X \to Y \in G \f$, there is no such
 *     a \f$ X^{'} \subset X \f$ where \f$ X^{'} \to Y \in G \f$.
 *   * For every \f$ X \to Y \in G \f$, there is no such
 *     a \f$ Y^{'} \subset Y \f$ where
 *     \f$ (G - \{X \to Y\} + \{X \to Y^{'}\})^+ = G^+ \f$.
 *
 * Time complexity: \f$ O(|F|^2) \f$.
 *
 * See also: Corollary 2. in
 *   [Maier(1979, p. 335)](https://dl.acm.org/doi/10.1145/800135.804425)
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
fds lrminimum(const int N, const fds &F);

/*! \brief Quine-McCluskey algorithm.
 *
 * Compute minimum boolean expression.
 *
 * Time complexity: \f$ O(2^N) \f$.
 *
 * @param exprs: 2d-vector of chars ('0', '1', '-') indicating the boolean
 * expressions.
 */
bool_exprs qmc(bool_exprs exprs);

/*! \brief Mini determination.
 *
 * Given a set of functional dependencies \f$ F \f$, determine if:
 *
 *   * For every \f$ X \to Y \in F \f$, \f$ | Y | = 1 \f$.
 *   * \f$ F \f$ has fewest FDs.
 *   * With the previous constraint, \f$ F \f$ has fewest attributes.
 *
 * Time complexity: \f$ O(2^N) \f$.
 *
 * See also: The definition of Mini in [Peng & Xiao (2015, p.
 * 461)](https://doi.org/10.1007/s00236-015-0247-9).
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
bool is_mini(const int N, const fds &F);

/*! \brief Mini calculation.
 *
 * Given a set of functional dependencies \f$ F \f$, calculate \f$ G \f$
 * where:
 *
 *   * For every \f$ X \to Y \in G \f$, \f$ | Y | = 1 \f$.
 *   * \f$ G \f$ has fewest FDs.
 *   * With the previous constraint, \f$ G \f$ has fewest attributes.
 *
 * Time complexity: \f$ O(2^N) \f$.
 *
 * See also: The definition of Mini in [Peng & Xiao (2015, p.
 * 461)](https://doi.org/10.1007/s00236-015-0247-9).
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
fds mini(const int N, const fds &F);

/*! \brief Optimal determination.
 *
 * Given a set of functional dependencies \f$ F \f$, determine if:
 *
 *   * \f$ F \f$ has fewest FDs.
 *
 * Time complexity: \f$ O(x^N) \f$.
 *
 * See also: Optimize algorithm in [Peng & Xiao (2015, p.
 * 467)](https://doi.org/10.1007/s00236-015-0247-9).
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
bool is_optimal(const int N, const fds &F);

/*! \brief Optimal calculate.
 *
 * Given a set of functional dependencies \f$ F \f$, calculate \f$ G \f$:
 *
 *   * \f$ G \f$ has fewest FDs.
 *
 * Time complexity: \f$ O(x^N) \f$.
 *
 * See also: Optimize algorithm in [Peng & Xiao (2015, p.
 * 467)](https://doi.org/10.1007/s00236-015-0247-9).
 *
 * @param N: The number of attributes.
 * @param F: A set of functional dependencies.
 */
fds optimal(const int N, const fds &F);

/** @} */
} // namespace fdc
#endif
