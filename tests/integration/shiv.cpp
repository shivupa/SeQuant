#include <SeQuant/core/parse.hpp>
#include <SeQuant/core/runtime.hpp>
#include <SeQuant/core/tensor_canonicalizer.hpp>
#include <SeQuant/core/timer.hpp>
#include <SeQuant/domain/mbpt/context.hpp>
#include <SeQuant/domain/mbpt/convention.hpp>
#include <SeQuant/domain/mbpt/models/cc.hpp>

using namespace sequant;
using namespace sequant::mbpt;

int main(int argc, char* argv[]) {
  std::setlocale(LC_ALL, "en_US.UTF-8");
  std::wcout.precision(std::numeric_limits<double>::max_digits10);
  std::wcerr.precision(std::numeric_limits<double>::max_digits10);
  std::wcout.sync_with_stdio(false);
  std::wcerr.sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.UTF-8"));
  std::wcerr.imbue(std::locale("en_US.UTF-8"));
  std::wcout.sync_with_stdio(true);
  std::wcerr.sync_with_stdio(true);

  // read command line arguments
  const bool print = true;

  auto mr_isr = sequant::mbpt::make_mr_spaces();
  // sequant::detail::OpIdRegistrar op_id_registrar;
  sequant::set_default_context(sequant::Context(
      sequant::mbpt::make_mr_spaces(), Vacuum::SingleProduct,
      IndexSpaceMetric::Unit, BraKetSymmetry::conjugate, SPBasis::spinorbital));
  TensorCanonicalizer::register_instance(
      std::make_shared<DefaultTensorCanonicalizer>());

  const auto h1_cc =
      ex<Tensor>(optype2label.at(OpType::h), bra{L"a_1"}, ket{L"i_1"});
  // const auto h1_ca = ex<Tensor>(optype2label.at(OpType::h), bra{L"a_3"},
  // ket{L"x_1"}); const auto h1_aa =
  // sequant::mbpt::ex<Tensor>(optype2label.at(OpType::h), bra{L"a_1"},
  // ket{L"a_2"}); const auto h1_av =
  // sequant::mbpt::ex<Tensor>(optype2label.at(OpType::h), bra{L"a_1"},
  // ket{L"a_2"}); const auto h1_vv =
  // sequant::mbpt::ex<Tensor>(optype2label.at(OpType::h), bra{L"a_1"},
  // ket{L"a_2"}); const auto a =ex<Tensor>(L"a",bra{L"i_2", L"i_3"},ket{L"a_2",
  // L"a_3"});
  auto a = h1_cc;  // + h1_ca;
  std::wcout << "a" << to_latex_align(a) << std::endl;

  std::wstring inputs = L"h{a1;i1} + 1/2 g{a1,a2;i1,i2}";

  auto input_expr = parse_expr(inputs);
  std::wcout << to_latex(input_expr) << std::endl;
  // change to true to print stats
  Logger::instance().wick_stats = false;

  // call the compute_all function here
  // compute_all{NMAX, exc_manifold, str2type.at(eqn_type)}(print);
}
