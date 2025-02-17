#pragma once
#include "types.hpp"
#include <string_view>

namespace weapon::core {
    class i_observable {
    public:
        virtual ~i_observable() = default;
        virtual void notify_observers() = 0;
    };

    class i_observer {
    public:
        virtual ~i_observer() = default;
        virtual void on_change() = 0;
    };

    class i_identifiable {
    public:
        virtual ~i_identifiable() = default;
        [[nodiscard]] virtual std::string_view get_id() const noexcept = 0;
        [[nodiscard]] virtual std::string_view get_name() const noexcept = 0;
    };

} // namespace weapon::core