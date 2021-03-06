//
// Copyright 2018 coord.e
//
// This file is part of flom-py.
//
// flom-py is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// flom-py is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with flom-py.  If not, see <http://www.gnu.org/licenses/>.
//

#include <flom/motion.hpp>
#include <flom/range.hpp>

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "declarations.hpp"

namespace flom_py {

namespace py = pybind11;

void define_motion(py::module &m) {
  py::class_<flom::EffectorType>(m, "EffectorType")
      .def_readwrite("location", &flom::EffectorType::location)
      .def_readwrite("rotation", &flom::EffectorType::rotation);

  m.def("load", [](std::string const &filename) {
    std::ifstream f(filename, std::ios::binary);
    return flom::Motion::load(f);
  });
  m.def("load_json", [](std::string const &filename) {
    std::ifstream f(filename);
    return flom::Motion::load_json(f);
  });
  m.def("load_json_string", &flom::Motion::load_json_string);

  py::class_<flom::Motion>(m, "Motion")
      .def(py::init<std::unordered_set<std::string>,
                    std::unordered_set<std::string>, std::string>(),
           py::arg("joint_names"), py::arg("effector_names"), py::arg("model"))
      .def("dump",
           [](flom::Motion const &motion, std::string const &filename) {
             std::ofstream f(filename, std::ios::binary);
             motion.dump(f);
           })
      .def("dump_json",
           [](flom::Motion const &motion, std::string const &filename) {
             std::ofstream f(filename);
             motion.dump_json(f);
           })
      .def("dump_json_string", &flom::Motion::dump_json_string)
      .def("frame_at", &flom::Motion::frame_at)
      .def("frames", &flom::Motion::frames)
      .def("loop", &flom::Motion::loop)
      .def("set_loop", &flom::Motion::set_loop)
      .def("model_id", &flom::Motion::model_id)
      .def("set_model_id", &flom::Motion::set_model_id)
      .def("effector_type", &flom::Motion::effector_type)
      .def("set_effector_type", &flom::Motion::set_effector_type)
      .def("is_in_range_at", &flom::Motion::is_in_range_at)
      .def("length", &flom::Motion::length)
      .def("joint_names", &flom::Motion::joint_names)
      .def("effector_names", &flom::Motion::effector_names)
      .def(py::self == py::self);
}

} // namespace flom_py
