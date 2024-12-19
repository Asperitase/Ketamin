#ifndef WATERMARK_HPP
#define WATERMARK_HPP

#include "../feature.hpp"

namespace feature::visual::watermark {

    class c_watermark final : public c_feature {
    public:
        explicit c_watermark() noexcept;
        ~c_watermark() noexcept override = default;
        void on_enable() noexcept final;
        void on_disable() noexcept final;
        void on_draw() noexcept final;
        void on_menu() noexcept final;
        // private:
        //	std::shared_ptr<c_setting> testbool;
    };
} // namespace feature::visual::watermark

#endif // !WATERMARK_HPP
