#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "feature.hpp"

#include <unordered_map>

namespace feature {
    /**
     * @brief Singleton class responsible for managing and handling features.
     *
     * The manager holds a collection of features, provides access to them, and handles
     * the drawing and menu interactions of the features. It is a singleton, ensuring
     * only one instance of the feature manager exists.
     */
    class c_manager final {
    public:
        /**
         * @brief Default constructor for the c_manager class.
         * Initializes the feature manager and adds default features to the collection.
         */
        c_manager() noexcept;

        /**
         * @brief Destructor for the c_manager class.
         * Automatic cleans up the features managed by the manager.
         */
        ~c_manager() noexcept = default;

        c_manager( const c_manager& ) = delete;            ///< Delete copy constructor to prevent copying.
        c_manager& operator=( const c_manager& ) = delete; ///< Delete copy assignment operator.
        c_manager( c_manager&& ) = delete;                 ///< Delete move constructor.
        c_manager& operator=( c_manager&& ) = delete;      ///< Delete move assignment operator.

        /**
         * @brief Gets the singleton instance of the feature manager.
         *
         * @return The instance of the c_manager.
         */
        [[nodiscard]] static c_manager& instance() noexcept;

    public:
        /**
         * @brief Retrieves all features managed by the manager.
         *
         * @return A reference to the unordered map containing all features.
         */
        [[nodiscard]] const std::unordered_map<std::string_view, std::unique_ptr<c_feature>>& get_feature() const noexcept;

        /**
         * @brief Retrieves a feature by its name.
         *
         * @param name The name of the feature to retrieve.
         * @return A pointer to the feature with the given name, or nullptr if not found.
         */
        [[nodiscard]] c_feature* get_feature_by_name( const std::string_view& name ) const noexcept;

        /**
         * @brief Calls the on_draw method for all enabled features.
         *
         * Iterates through all features and calls their drawing methods if they are enabled.
         */
        void on_draw() const noexcept;

        /**
         * @brief Displays the menu for the features.
         *
         * Organizes features into tabs based on their categories and displays them in the UI.
         */
        void on_menu() const noexcept;

    private:
        /**
         * @brief Adds a feature to the manager.
         *
         * @param name The name of the feature to add.
         * @param feature A pointer to the feature to add.
         */
        template <typename T>
        void add_feature( const std::string_view& name ) noexcept;

        std::unordered_map<std::string_view, std::unique_ptr<c_feature>> features; ///< Map of feature names to feature pointers.
    };
} // namespace feature

#endif // !MANAGER_HPP
