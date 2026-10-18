#ifndef PULSE_HPP
#define PULSE_HPP

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct pulseState {
    int count;

    explicit pulseState(): count(0) {
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const pulseState& state) {
    out  << "{count: " << state.count << "}";
    return out;
}
#endif

class pulse : public Atomic<pulseState> {
    public:
    Port<int> out;

    pulse(const std::string id) : Atomic<pulseState>(id, pulseState()) {
        out = addOutPort<int>("out");
    }

    void internalTransition(pulseState& state) const override {
        state.count ++;
    }

    void externalTransition(pulseState& state, double e) const override {
        // nothing to do: this model has no inputs
    }

    void output(const pulseState& state) const override {
        out->addMessage(state.count);
    }

    [[nodiscard]] double timeAdvance(const pulseState& state) const override {
        return 3;
    }
};

#endif

