#ifndef _RESULT_HPP
#define _RESULT_HPP

#include <memory>
#include <exception>
#include <functional>
#include <stdexcept>

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
            throw std::runtime_error("Tried to access an already consumed result");
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
        Result(const Result<TValue>& other);
        Result(Result<TValue>& other);
        ~Result() noexcept {};

        constexpr bool match(
            std::function<void(TValue&&)> success,
            std::function<void(const std::exception*)> failure
        );
        constexpr bool match(
            std::function<void(const TValue&&)> success,
            std::function<void(const std::exception*)> failure
        ) const;

        TValue& unpack();
        const TValue& unpack() const;
        constexpr bool success_status() const noexcept;
    };

    #include "result.ipp"

    template <typename TValue>
    struct Result<std::unique_ptr<TValue>>
    {
    private:
        const bool is_failure_;
        bool is_used_ = false;

        std::unique_ptr<TValue> value_;
        std::unique_ptr<std::exception> failure_;

        auto throw_used() const -> void {
            throw std::runtime_error("Tried to access an already consumed result");
        }
    
    public:
        Result(std::unique_ptr<TValue> value) noexcept;
        Result(std::exception* exc) noexcept :
            value_{},
            failure_(std::unique_ptr<std::exception>(exc)),
            is_failure_(true) {};
        Result(const Result<std::unique_ptr<TValue>>& other);
        Result(Result<std::unique_ptr<TValue>>& other);
        ~Result() noexcept {};

        constexpr bool match(
            std::function<void(std::unique_ptr<TValue>)> success,
            std::function<void(const std::exception*)> failure
        );
        constexpr bool match(
            std::function<void(TValue*)> success,
            std::function<void(const std::exception*)> failure
        ) const;
        constexpr bool match_r(
            std::function<void(TValue*)> success,
            std::function<void(const std::exception*)> failure
        );

        std::unique_ptr<TValue> unpack();
        TValue* unpack_n() const;
        TValue* unpack_r();
        constexpr bool success_status() const noexcept;
    };

    #include "result_up.ipp"

} // namespace tools

#endif // !_RESULT_HPP