/**
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2022-present Román Cárdenas Rodríguez
 * ARSLab - Carleton University
 */

#ifndef CADMIUM_EXAMPLE_CELLDEVS_FIRE_STATE_HPP_
#define CADMIUM_EXAMPLE_CELLDEVS_FIRE_STATE_HPP_

#include <iostream>
#include <nlohmann/json.hpp>

namespace cadmium::celldevs::example::fire {
	//! Susceptible-Infected-Recovered state.
	struct FireState {
		int status; //!<0 = unburnt, 1 = burning, 2 = burnt.
		int timer; //!< Steps of burning left.

		//! Default constructor function. By default, cells are unburnt and without a timer.
		FireState() : status(0), timer(0) {
		}
	};

	//! It returns true if x and y are different.
	inline bool operator!=(const FireState& x, const FireState& y) {
		return x.status != y.status || x.timer != y.timer;
	}

	//! It prints a state and timer in an output stream.
	std::ostream& operator<<(std::ostream& os, const FireState& x) {
		os << "<" << x.status << "," << x.timer << ">";
		return os;
	}

	//! It parses a JSON file and generates the corresponding cell.
	void from_json(const nlohmann::json& j, FireState& s) {
		j.at("status").get_to(s.status);
		j.at("timer").get_to(s.timer);
	}
}
#endif
