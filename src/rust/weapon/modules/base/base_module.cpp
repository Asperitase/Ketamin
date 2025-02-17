#include "base_module.hpp"

namespace weapon::modules {

    template <core::ModuleValue T>
    module_base<T>::module_base( std::string_view name, T value ) noexcept: m_name( name ), m_value( value ), m_enabled( false ) { }

    template <core::ModuleValue T>
    std::string_view module_base<T>::get_name() const noexcept {
        return m_name;
    }

    template <core::ModuleValue T>
    bool module_base<T>::is_enabled() const noexcept {
        return m_enabled;
    }

    template <core::ModuleValue T>
    void module_base<T>::set_enabled( bool state ) noexcept {
        m_enabled = state;
    }

    template <core::ModuleValue T>
    T module_base<T>::get_value() const noexcept {
        return m_value;
    }

    template <core::ModuleValue T>
    void module_base<T>::set_value( T value ) noexcept {
        m_value = value;
    }

    template class module_base<int>;
    template class module_base<float>;

} // namespace weapon::modules