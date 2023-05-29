#ifndef _RESULT_HPP
#define _RESULT_HPP

#include <memory>
#include <exception>
#include <functional>

namespace tools
{

    template <typename TValue>
    struct Result
    {
    private:
        const bool is_failure_;
        bool is_used_ = false;
        TValue value_;
        std::unique_ptr<std::exception> failure_;

        auto throw_used() const -> void { 
            throw std::exception("Tried to access an already consumed result");
        }

    public:
        Result(const TValue& value) noexcept : 
            value_(value),
            is_failure_(false) {};
        Result(TValue& value) noexcept :
            value_(value),
            is_failure_(false) {};
        Result(std::exception* exc) noexcept :
            value_{},
            failure_(std::unique_ptr<std::exception>(exc)),
            is_failure_(true) {};
        Result(const Result<TValue>& other) noexcept;
        Result(Result<TValue>& other) noexcept;
        ~Result() noexcept {};

        constexpr bool match(
            std::function<void(TValue&&)> success,
            std::function<void(const std::exception*)> failure
        ) noexcept;
        constexpr bool match(
            std::function<void(const TValue&&)> success,
            std::function<void(const std::exception*)> failure
        ) const noexcept;

        TValue& unpack();
        const TValue& unpack() const;
        constexpr bool success_status() const noexcept;
    };

    #include "result.ipp"

} // namespace tools

#endif // !_RESULT_HPP