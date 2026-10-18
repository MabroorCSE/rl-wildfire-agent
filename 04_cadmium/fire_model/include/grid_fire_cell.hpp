#ifndef CADMIUM_EXAMPLE_CELLDEVS_FIRE_GRID_CELL_HPP_
#define CADMIUM_EXAMPLE_CELLDEVS_FIRE_GRID_CELL_HPP_

#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "state.hpp"

namespace cadmium::celldevs::example::fire {
	class GridFireCell : public GridCell<FireState, double> {
		int burn;  // steps a cell burns before it is burnt
	 public:
		GridFireCell(const std::vector<int>& id, const std::shared_ptr<const GridCellConfig<FireState, double>>& config):
		  GridCell<FireState, double>(id, config), burn() {
			config->rawCellConfig.at("burn").get_to(burn);
		}

		[[nodiscard]] FireState localComputation(FireState state,
		  const std::unordered_map<std::vector<int>, NeighborData<FireState, double>>& neighborhood) const override {
			if (state.status == 0) {
				for (const auto& [neighborId, neighborData]: neighborhood) {
					if (neighborData.state->status == 1) {
						state.status = 1;
						state.timer = burn;
					}
				}
			} else if (state.status == 1) {
				state.timer -= 1;
				if (state.timer <= 0) {
					state.status = 2;
				}
			}
			return state;
		}

		[[nodiscard]] double outputDelay(const FireState& state) const override {
			return 1.;
		}
	};
}  // namespace cadmium::celldevs::example::fire

#endif