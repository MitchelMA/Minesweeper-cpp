#ifndef _RESULT_IPP
#define _RESULT_IPP

template <typename TValue>
Result<TValue>::Result(
    const Result<TValue>& other
) :
    is_failure_(other.is_failure_),
    is_used_(other.is_used_),
    value_(std::move(other.value_))
{
    if (is_used_) throw_used();

    if (is_failure_)
        failure_ = std::make_unique<std::exception>(std::forward<std::exception>(*other.failure_));
}

template <typename TValue>
Result<TValue>::Result(
    Result<TValue>& other
) :
    is_failure_(other.is_failure_),
    is_used_(other.is_used_),
    value_(std::move(other.value_))
{
    if (is_used_) throw_used();

    if (is_failure_)
        failure_ = std::make_unique<std::exception>(std::forward<std::exception>(*other.failure_));
}

template <typename TValue>
Result<TValue>::Result(
    Result<TValue>&& other
) :
    is_failure_(other.is_failure_),
    is_used_(other.is_used_),
    value_(std::move(other.value_))
{
    if (is_used_) throw_used();
    else other.is_used_ = true;

    if (is_failure_)
        failure_ = std::make_unique<std::exception>(std::forward<std::exception>(*other.failure_));
}

template <typename TValue>
constexpr bool
Result<TValue>::match(
    const std::function<void(TValue&&)>& success,
    const std::function<void(const std::exception*)>& failure
)
{
    if(is_used_)
        throw_used();

    if(is_failure_)
    {
        std::invoke(std::forward<const std::function<void(const std::exception*)>&>(failure), failure_.get());
        return false;
    }

    std::invoke(std::forward<const std::function<void(TValue&&)>&>(success), std::forward<TValue>(value_.value()));
    return true;
}

template <typename TValue>
constexpr bool
Result<TValue>::match(
    const std::function<void(const TValue&&)>& success,
    const std::function<void(const std::exception*)>& failure
) const
{
    if(is_used_)
        throw_used();

    if(is_failure_)
    {
        std::invoke(std::forward<const std::function<void(const std::exception*)>&>(failure), failure_.get());
        return false;
    }

    std::invoke(std::forward<const std::function<void(const TValue&&)>&>(success), std::forward<const TValue>(value_.value()));
    return true;
}

template <typename TValue>
TValue&
Result<TValue>::unpack()
{
    if(is_used_) throw_used();

    if(is_failure_)
        throw std::exception(*failure_);

    return value_.value();
}

template <typename TValue>
const TValue&
Result<TValue>::unpack()
const
{
    if(is_used_) throw_used();

    if(is_failure_)
        throw std::exception(*failure_);

    return value_.value();
}

template <typename TValue>
constexpr bool
Result<TValue>::success_status()
const noexcept
{
    return !is_failure_;
}


#endif // !_RESULT_IPP
